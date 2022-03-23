#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <queue>
#include <unordered_map>

std::unordered_map<std::string, std::uint32_t> build_tree(const std::unordered_map<std::string, std::uint32_t> &data);

#endif