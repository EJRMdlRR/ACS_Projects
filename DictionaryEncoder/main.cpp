#include <vector>
#include <array>
#include <algorithm>
#include <chrono>

#include "huffman.h"

std::string b95_encode(std::uint32_t value)
{
    std::array<std::uint32_t, 4> positions{81450625, 857375, 9025, 95};
    std::string new_encoding = "";

    for (auto &position : positions)
    {
        std::uint32_t div = value / position;
        if (div >= 1)
        {
            new_encoding += char(32 + div);
            value -= position * div;
        }
    }

    new_encoding += char(32 + value);
    new_encoding[0] = new_encoding[0] | 0b10000000;

    return new_encoding;
}

std::uint32_t b95_decode(std::string coded_word)
{
    std::array<std::uint32_t, 5> positions{{81450625, 857375, 9025, 95, 1}};
    std::uint32_t value = 0;
    std::uint8_t MSB = coded_word.size();
    coded_word[0] = coded_word[0] & 0b01111111;

    for (std::uint8_t letter = 0; letter < MSB; letter++)
    {
        value += ((int)coded_word[letter] - 32) * positions[MSB - letter];
    }

    return value;
}

std::unordered_map<std::string, std::string> b95_compress(const std::unordered_map<std::string, std::uint32_t> &coding)
{
    std::unordered_map<std::string, std::string> new_coding;
    for (auto &word : coding)
    {
        std::string new_code = b95_encode(word.second);
        new_coding[word.first] = new_code;
    }

    return new_coding;
};

void error_checks(const std::uint32_t &argc,
                  const char **argv)
{
    std::string op = argv[1];
    if (op == "-h" || op == "--help" || op == "HELP")
    {
        std::cout << "USAGE: " << argv[0] << " ENCODE/DECODE"
                  << " <FILE TO ENCODE/DECODE>" << std::endl;
        std::cout << "For Help: " << argv[0] << " HElP" << std::endl;
        exit(1);
    }
    else if (argc < 3)
    {
        std::cout << "Too few arguments. See help with \"HELP\" for proper usage." << std::endl;
        exit(1);
    }
    else if (argc > 3)
    {
        std::cout << "Too many arguments. See help with \"HELP\" for proper usage." << std::endl;
        exit(1);
    }
    else if (std::string(op) != "ENCODE" && op != "DECODE")
    {
        std::cout << "Only valid actions are \"ENCODE\" or \"DECODE\". Not " << op << std::endl;
        exit(1);
    }
    else
    {
        std::ifstream file(argv[2]);
        if (file.fail())
        {
            std::cerr << "Could not open file " << argv[2] << std::endl;
            exit(1);
        }
        file.close();
    }
}

void load_and_analyze(const std::string &filename,
                      std::unordered_map<std::string, std::uint32_t> &frequencies)
{
    std::cout << ":: LOADING FILE \"" << filename << "\" ::" << std::endl;
    std::string line;
    std::ifstream datafile(filename);
    while (datafile >> line)
    {
        frequencies[line]++;
    }
    datafile.close();
}

void huffman_to_json(const std::string &prefix,
                     const std::unordered_map<std::string, std::string> &code)
{
    std::cout << ":: WRITING ENCODING KEY ::" << std::endl;

    std::ofstream file(prefix + "_encoded.tsv");
    for (auto &word : code)
    {
        std::string temp = word.second;
        temp[0] = temp[0] & 0b01111111;
        file << temp << "\t" << word.first << "\n";
    }
    file.close();
}

void write_coded(const std::string &filename,
                 const std::unordered_map<std::string, std::string> &code)
{
    std::cout << ":: WRITING ENCODED FILE ::" << std::endl;
    std::string line;
    std::ifstream datafile(filename);

    std::string prefix = filename.substr(0, filename.find("."));
    std::ofstream outfile(prefix + "_encoded.txt");

    while (datafile >> line)
    {
        outfile << code.at(line);
    }

    outfile.close();
    datafile.close();
}

std::unordered_map<std::string, std::string> load_coding(const std::string &prefix)
{
    std::cout << ":: LOADING CODE ::" << std::endl;
    std::unordered_map<std::string, std::string> code;
    std::string line;
    std::string word;

    std::ifstream codefile(prefix + ".tsv");

    while (std::getline(codefile, line))
    {
        word = line.substr(0, line.find('\t'));
        line = line.erase(0, line.find('\t') + 1);
        code[word] = line;
    }

    codefile.close();

    return code;
}

void decode(const std::string &filename,
            const std::string &prefix,
            const std::unordered_map<std::string, std::string> &code)
{
    char ch;
    std::string word = "";
    std::string temp = "";

    std::ifstream datafile(filename);
    std::ofstream outfile(prefix + "_decoded.txt");

    std::cout << ":: DECODING ::" << std::endl;
    while (datafile >> std::noskipws >> ch)
    {
        if (ch & 0b10000000 && word != "")
        {
            outfile << code.at(word) << std::endl;
            word = ch & 0b01111111;
        }
        else if (ch & 0b10000000)
            word = ch & 0b01111111;
        else
            word += ch;
    }
    outfile << code.at(word) << std::endl;
    
    outfile.close();
    datafile.close();
}

int main(int argc, const char **argv)
{
    error_checks(argc, argv);

    const std::string op = argv[1];
    const std::string filename = argv[2];
    std::unordered_map<std::string, std::uint32_t> frequencies;

    if (op == "ENCODE")
    {
        auto start = std::chrono::high_resolution_clock::now();
        load_and_analyze(filename, frequencies);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Dataset Analysis: " << duration.count() * 1e-6 << "s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        std::unordered_map<std::string, std::string> code = b95_compress(build_tree(frequencies));
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Encoding: " << duration.count() * 1e-6 << "s" << std::endl;

        std::string prefix = filename.substr(0, filename.find("."));

        start = std::chrono::high_resolution_clock::now();
        huffman_to_json(prefix, code);
        write_coded(filename, code);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Writing Output: " << duration.count() * 1e-6 << "s" << std::endl;
    }
    else if (std::string(argv[1]) == "DECODE")
    {
        std::string prefix = filename.substr(0, filename.find('.'));
        auto start = std::chrono::high_resolution_clock::now();
        std::unordered_map<std::string, std::string> code = load_coding(prefix);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Code Loading: " << duration.count() * 1e-6 << "s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        decode(filename, prefix, code);
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Decoding: " << duration.count() * 1e-6 << "s" << std::endl;
    }
    return 0;
}