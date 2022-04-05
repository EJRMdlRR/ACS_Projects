#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <filesystem>

#include "huffman.h"

typedef std::string str;
typedef std::uint32_t uint32;

str b128_encode(uint32 value)
{
    std::array<uint32, 4> positions{268435456, 2097152, 16384, 128};
    str new_encoding = "";

    for (auto &position : positions)
    {
        uint32 div = value / position;
        if (div >= 1)
        {
            new_encoding += (char)div;
            value -= position * div;
        }
    }

    new_encoding += (char)value;
    new_encoding[0] = new_encoding[0] | 0b10000000;

    return new_encoding;
}

uint32 b128_decode(str coded_word)
{
    std::array<uint32, 5> positions{268435456, 2097152, 16384, 128, 1};
    uint32 value = 0;
    std::uint8_t MSB = coded_word.size();
    coded_word[0] = coded_word[0] & 0b01111111;

    for (std::uint8_t letter = 0; letter < MSB; letter++)
    {
        value += (uint32)coded_word[letter] * positions[MSB - letter];
    }

    return value;
}

std::unordered_map<str, str> b128_compress(const std::unordered_map<str, uint32> &coding)
{
    std::unordered_map<str, str> new_coding;
    for (auto &word : coding)
    {
        str new_code = b128_encode(word.second);
        new_coding[word.first] = new_code;
    }

    return new_coding;
};

void error_checks(const uint32 &argc,
                  const char **argv)
{
    str op = argv[1];
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
    else if (str(op) != "ENCODE" && op != "DECODE")
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

void load_and_analyze(const str &filename,
                      std::unordered_map<str, uint32> &frequencies)
{
    str line;
    std::ifstream datafile(filename);
    while (datafile >> line)
    {
        frequencies[line]++;
    }
    datafile.close();
}

str write_encoding(const str &prefix,
                   const std::unordered_map<str, str> &code)
{
    std::ofstream file(prefix + "_encoded.enc");
    for (auto &word : code)
    {
        str temp = word.first;
        temp[0] = temp[0] | 0b10000000;
        file << word.second << temp;
    }
    file.close();
    return prefix + "_encoded.enc";
}

str write_encoded(const str &filename,
                  const std::unordered_map<str, str> &code)
{
    str line;
    std::ifstream datafile(filename);

    str prefix = filename.substr(0, filename.find("."));
    std::ofstream outfile(prefix + "_encoded.bin");

    while (datafile >> line)
    {
        outfile << code.at(line);
    }

    outfile.close();
    datafile.close();
    return prefix + "_encoded.bin";
}

std::unordered_map<str, str> load_coding(const str &prefix)
{
    std::unordered_map<str, str> code;
    str word = "", temp = "";
    char ch;

    std::ifstream codefile(prefix + ".enc");

    while (codefile >> std::noskipws >> ch)
    {
        if (ch & 0b10000000 and word == "")
        {
            word = temp;
            temp = ch & 0b01111111;
        }
        else if (ch & 0b10000000)
        {
            code[word] = temp;
            word = temp = "";
            temp = ch & 0b01111111;
        }
        else
        {
            temp += ch;
        }
    }
    code[word] = temp;
    codefile.close();

    return code;
}

void decode(const str &filename,
            const str &prefix,
            const std::unordered_map<str, str> &code)
{
    char ch;
    str word = "";
    str temp = "";

    std::ifstream datafile(filename);
    std::ofstream outfile(prefix + "_decoded.txt");

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

    const str op = argv[1];
    const str filename = argv[2];
    std::unordered_map<str, uint32> frequencies;

    if (op == "ENCODE")
    {
        auto start = std::chrono::high_resolution_clock::now();
        load_and_analyze(filename, frequencies);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Dataset Analysis: " << duration.count() * 1e-6 << "s" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        std::unordered_map<str, str> code = b128_compress(build_tree(frequencies));
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Encoding: " << duration.count() * 1e-6 << "s" << std::endl;

        str prefix = filename.substr(0, filename.find("."));

        start = std::chrono::high_resolution_clock::now();
        str encoding_file = write_encoding(prefix, code);
        str encoded_file = write_encoded(filename, code);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Writing Output: " << duration.count() * 1e-6 << "s" << std::endl;

        std::cout << filename << " size = " << std::filesystem::file_size(std::filesystem::current_path() / filename) << '\n';
        std::cout << encoding_file << " size = " << std::filesystem::file_size(std::filesystem::current_path() / encoding_file) << '\n';
        std::cout << encoded_file << " size = " << std::filesystem::file_size(std::filesystem::current_path() / encoded_file) << '\n';
    }
    else if (str(argv[1]) == "DECODE")
    {
        str prefix = filename.substr(0, filename.find('.'));
        auto start = std::chrono::high_resolution_clock::now();
        std::unordered_map<str, str> code = load_coding(prefix);
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
