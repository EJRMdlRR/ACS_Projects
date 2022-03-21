import pathlib
import argparse
import pprint
import collections


class NodeTree:
    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right

    def children(self):
        return (self.left, self.right)

    def nodes(self):
        return (self.left, self.right)


def encode(node, code=""):
    if isinstance(node, str):
        return {node: code}

    l, r = node.children()
    d = {}
    d.update(encode(l, f"{code}0"))
    d.update(encode(r, f"{code}1"))

    return d


def gain(freq, coding):
    before = after = 0

    for word in freq:
        before += len(word) * 8 * freq[word]
        after += len(coding[word]) * freq[word]

    print("Space usage before compression (in bits):", before)
    print("Space usage after compression (in bits): ", after)
    print(f"Reduction: {100-100*after/before:.2f}%")


if __name__ == "__main__":
    pp = pprint.PrettyPrinter().pprint
    parser = argparse.ArgumentParser(description="Enter filename to analyze data for.")
    parser.add_argument(
        "filename",
        metavar="F",
        type=pathlib.Path,
        nargs="+",
        help="filename/s containing dataset to be analyzed. File must have full path or be in cwd.",
    )

    parser.add_argument(
        "-D",
        "--delimiter",
        metavar="D",
        default="\n",
        help="sum the integers (default: find the max)",
    )

    args = parser.parse_args()

    data = []
    for filename in args.filename:
        with filename.open() as file:
            data.extend(file.read().split(args.delimiter))
    freq = collections.Counter(data)

    nodes = list(freq.items())

    while len(nodes) > 1:
        nodes = sorted(nodes, key=lambda x: x[1], reverse=True)
        (key1, c1) = nodes[-1]
        (key2, c2) = nodes[-2]
        nodes = nodes[:-2]
        node = NodeTree(key1, key2)
        nodes.append((node, c1 + c2))

    huffman_code = encode(nodes[0][0])

    print(" Char | Freq | Huffman code ")
    print("----------------------")
    for char in sorted(freq.keys(), key=freq.get, reverse=True):
        print(f"{char:10s} | {freq[char]:4} | {huffman_code[char]:>11s}")

    gain(freq, huffman_code)
