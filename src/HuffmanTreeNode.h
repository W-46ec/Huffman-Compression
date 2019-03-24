/*
 * HuffmanTreeNode.h
 *
 * Description: Node of Huffman tree.
 * Class Invariant: Each node is either of type tree_node or char_node.
 *
 *
 *
 */

#ifndef HUFFMANTREENODE_H
#define HUFFMANTREENODE_H

#include <string>

using namespace std;

// Desc: The type of tree node.
typedef enum HuffmanTreeNodeType {
	tree_node, char_node
} NodeType;

class HuffmanTreeNode {
public:
	NodeType type;		// Either "tree_node" or "char_node".
	unsigned weight;
	HuffmanTreeNode *lChild, *rChild, *parent;

	char character;
	unsigned code;
	unsigned codeLength;	// Length of code

	// Constructors
	HuffmanTreeNode();
	HuffmanTreeNode(NodeType type, unsigned weight, char character);
	HuffmanTreeNode(NodeType type, unsigned weight, HuffmanTreeNode *left, HuffmanTreeNode *right, HuffmanTreeNode *parent);

	// Desc:  Comparators
	bool operator < (const HuffmanTreeNode &node) const;
	bool operator <= (const HuffmanTreeNode &node) const;
	bool operator > (const HuffmanTreeNode &node) const;
	bool operator >= (const HuffmanTreeNode &node) const;
	bool operator == (const HuffmanTreeNode &node) const;
}; // HuffmanTreeNode

#endif

// End of HuffmanTreeNode.h
