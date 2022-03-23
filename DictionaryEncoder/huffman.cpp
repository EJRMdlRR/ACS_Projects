#include "huffman.h"

struct Node
{
    std::string word;
    std::uint32_t freq;
    Node *left, *right;
};

struct comp
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

Node *new_node(std::string word, std::uint32_t freq)
{
    Node *node = new Node();

    node->word = word;
    node->freq = freq;
    node->left = node->right = nullptr;

    return node;
}

Node *get_node(std::string word,
               std::uint32_t freq,
               Node *left,
               Node *right)
{
    Node *node = new Node();

    node->word = word;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

void encode(Node *root,
            std::string str,
            std::unordered_map<std::string, std::uint32_t> &code)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        code[root->word] = std::stoi(str, nullptr, 2);
    }

    encode(root->left, str + "0", code);
    encode(root->right, str + "1", code);
}

std::unordered_map<std::string, std::uint32_t> build_tree(const std::unordered_map<std::string, std::uint32_t> &data)
{
    std::priority_queue<Node *, std::vector<Node *>, comp> pq;

    for (auto pair : data)
        pq.push(new_node(pair.first, pair.second));

    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        std::uint32_t sum = left->freq + right->freq;
        pq.push(get_node("", sum, left, right));
    }

    Node *root = pq.top();

    std::unordered_map<std::string, std::uint32_t> code;
    encode(root, "1", code);

    return code;
}