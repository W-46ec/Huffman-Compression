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

#include <iostream>
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

	// Desc: Print the code of the current node.
	void printCode() const;

	// Desc: Print the content of the node.
	//       Display a (type, weight, code) tuple for nodes of type "tree_node".
	//       Display a (type, weight, character, code) tuple for nodes of type "char_node".
	friend ostream &operator << (ostream &os, const HuffmanTreeNode* nodePtr);
}; // HuffmanTreeNode

#endif

// End of HuffmanTreeNode.h
