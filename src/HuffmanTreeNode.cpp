/*
 * HuffmanTreeNode.cpp
 *
 * Description: Node of Huffman tree.
 * Class Invariant: Each node is either of type tree_node or char_node.
 *
 *
 *
 */

#include "HuffmanTreeNode.h"


// Desc: Default constructor
HuffmanTreeNode::HuffmanTreeNode() {
	weight = 0;
	code = 0;
	codeLength = 0;
	lChild = NULL;
	rChild = NULL;
	parent = NULL;
} // Constructor

// Desc: Non-default constructor
HuffmanTreeNode::HuffmanTreeNode(NodeType type, unsigned weight, char character) {
	this -> type = type;
	this -> weight = weight;
	this -> character = character;
	code = 0;
	codeLength = 0;
	lChild = NULL;
	rChild = NULL;
	parent = NULL;
} // Non-default constructor

// Desc: Non-default constructor
HuffmanTreeNode::HuffmanTreeNode(NodeType type, unsigned weight, HuffmanTreeNode *left, HuffmanTreeNode *right, HuffmanTreeNode *parent) {
	code = 0;
	codeLength = 0;
	this -> type = type;
	this -> weight = weight;

	this -> lChild = left;
	if (lChild != NULL) {
		lChild -> parent = this;
	}

	this -> rChild = right;
	if (rChild != NULL) {
		rChild -> parent = this;
	}

	this -> parent = parent;
} // Non-default constructor

// Comparators

bool HuffmanTreeNode::operator < (const HuffmanTreeNode &node) const {
	return weight < node.weight;
} // operator <

bool HuffmanTreeNode::operator <= (const HuffmanTreeNode &node) const {
	return weight <= node.weight;
} // operator <=

bool HuffmanTreeNode::operator > (const HuffmanTreeNode &node) const {
	return weight > node.weight;
} // operator >

bool HuffmanTreeNode::operator >= (const HuffmanTreeNode &node) const {
	return weight >= node.weight;
} // operator >=

bool HuffmanTreeNode::operator == (const HuffmanTreeNode &node) const {
	return weight == node.weight;
} // operator ==

// End of HuffmanTreeNode.cpp
