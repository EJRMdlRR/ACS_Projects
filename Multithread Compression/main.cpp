#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <zstd.h>
#include <ios>
#include <thread>
#include <math.h>
#include <chrono>
#include "ThreadSafeQueue.h"

#define BLOCK 16 * 1024

void file_reader(thread_safe_queue *blocks, char *f, int *read_done)
{
    unsigned long int idx = 0;
    std::ifstream in(f);
    while (!in.eof())
    {
        char *temp = new char[BLOCK];
        in.read(temp, BLOCK);
        blocks->push_back(std::tuple<int, int, char *>(in.gcount(), idx, temp));
        idx++;
    }
    in.close();
    (*read_done) = 1;
}

void file_writer(std::vector<char *> *compressed_blocks, std::vector<int> *compressed_block_sizes, std::string file, long unsigned int *total_blocks)
{
    std::ofstream out(file);
    long unsigned int idx = 0;
    int vect_idx = 0;
    while (idx < (*total_blocks))
    {
        while ((*compressed_block_sizes)[vect_idx] == 0)
        {
        }
        out.write((*compressed_blocks)[vect_idx], (*compressed_block_sizes)[vect_idx]);
        (*compressed_block_sizes)[vect_idx] = 0;
        idx++;
        vect_idx = idx % (compressed_block_sizes->size());
    }
    out.close();
}

void compressor(thread_safe_queue *blocks, std::vector<char *> *compressed_blocks, std::vector<int> *compressed_block_sizes, int *read_done, unsigned int *NTHREADS, size_t *C_BLOCK)
{
    std::tuple<int, int, char *> block;
    while (blocks->size() || !(*read_done))
    {
        if (!(blocks->pop_front(block)))
        {
            continue;
        }
        int pos = std::get<1>(block) % ((*NTHREADS) * 16);
        while ((*compressed_block_sizes)[pos] != 0)
        {
        }

        size_t compressedSize = ZSTD_compress((*compressed_blocks)[pos], *C_BLOCK, std::get<2>(block), std::get<0>(block), 1);
        (*compressed_block_sizes)[pos] = compressedSize;
    }
}

int main(int argc, char *argv[])
{
    // Set NTHREADS, the number of threads; in, the input filestream; and out, the output filestream
    // out is optional and defaults to <IN_FILENAME>.zst
    // NTHREADS is optional and defaults to 8
    thread_safe_queue blocks;
    int read_done = 0;

    std::streampos begin;
    std::ifstream f(argv[1], std::ios::binary);
    begin = f.tellg();
    f.seekg(0, std::ios::end);
    long unsigned int total_blocks = ceil((f.tellg() - begin) / (float)(BLOCK));
    f.close();

    std::thread reader(file_reader, &blocks, argv[1], &read_done);

    unsigned int NTHREADS = 16;
    std::string file = (std::string)argv[1];
    file = file.substr(0, file.find('.')) + ".zst";

    if (argc == 4)
    {
        NTHREADS = std::stoi(argv[3]);
        file = argv[2];
    }
    else if (argc == 3 || argc == 2)
    {
        try
        {
            NTHREADS = std::stoi(argv[2], nullptr);
        }
        catch (std::invalid_argument const &ex)
        {
            file = argv[2];
        }
        catch (...)
        {
        }
    }

    // Setup Environment for future multi-threading.
    // e.g. setup input queue and output vector
    size_t C_BLOCK = ZSTD_compressBound(BLOCK);
    std::vector<char *> compressed_blocks;
    std::vector<int> compressed_block_sizes(NTHREADS * 16, 0);
    compressed_blocks.reserve(NTHREADS * 16);
    for (unsigned int i = 0; i < NTHREADS * 16; ++i)
    {
        compressed_blocks.push_back(new char[C_BLOCK]);
    }

    std::thread writer(file_writer, &compressed_blocks, &compressed_block_sizes, file, &total_blocks);
    // Read and compress file
    std::vector<std::thread> compressors;
    for (unsigned int i = 0; i < NTHREADS * 16; i++)
    {
        compressors.push_back(std::thread(compressor, &blocks, &compressed_blocks, &compressed_block_sizes, &read_done, &NTHREADS, &C_BLOCK));
    }
    reader.join();
    for (unsigned int i = 0; i < NTHREADS * 16; i++)
    {
        compressors[i].join();
    }
    writer.join();
    return 0;
}