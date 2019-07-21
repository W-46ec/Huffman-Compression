/*
 * HuffmanTreeNode.cpp
 *
 * Description: Node of Huffman tree.
 * Class Invariant: Each node is either of type tree_node or char_node.
 *
 *
 *
 */

#include <iostream>
#include "HuffmanTreeNode.h"

using namespace std;

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

// Desc: Print the code of the current node.
void HuffmanTreeNode::printCode() const {
	unsigned pos = 0x1 << (codeLength - 1);
	for (unsigned i = 0; i < codeLength; i++) {
		(pos & code) == 0 ? cout << "0" : cout << "1";
		pos >>= 1;
	}
} // printCode

// Desc: Print the content of the node.
//       Display a (type, weight, code) tuple for nodes of type tree_node.
//       Display a (type, weight, character) tuple for nodes of type char_node.
ostream &operator << (ostream &os, const HuffmanTreeNode* nodePtr) {
	if (nodePtr == NULL) {
		os << "NULL";
	} else {
		unsigned w = nodePtr -> weight;
		if (nodePtr -> type == tree_node) {	// Tree node
			os << "(T, " << w << ", \"";
			nodePtr -> printCode();
			os << "\")";
		} else {		// Character node
			char c = nodePtr -> character;
			if (c >= 0x20 && c < 0x7F) {	// Printable characters
				os << "(C, " << w << ", \"" << c << "\", \"";
				nodePtr -> printCode();
				os << "\")";
			} else {	// Non-printable characters
				os << "C, " << w << ", '.', \"";
				nodePtr -> printCode();
				os << "\")";
			}
		}
	}
	return os;
} // operator <<

// End of HuffmanTreeNode.cpp
