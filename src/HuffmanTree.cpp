/*
 * HuffmanTree.cpp
 *
 * Description: HuffmanTree class
 *
 *
 *
 */

#include "HuffmanTree.h"
#include "PriorityQueue.h"
#include "HuffmanTreeNode.h"

#include <iostream>

using namespace std;

// Helper functions

// Desc: Traverse the Huffman tree and generate code for each node.
//  Pre: "direction" is one of 0, 1, or -1.
//       	 0: current tree node is the left child of the parent node;
//       	 1: current tree node is the right child of the parent node;
//       	-1: current tree node is the root (parent == NULL);
void HuffmanTree::generateCode(HuffmanTreeNode *tree, int direction) {
	if (tree == NULL)	// Base case
		return;

	if (tree -> parent != NULL) {
		tree -> code = tree -> parent -> code << 1;
		if (direction == 1)		// Right child
			tree -> code += 1;
		tree -> codeLength = tree -> parent -> codeLength + 1;
	}

	// Update the code tables.
	if (tree -> type == char_node) {
		codeTable[tree -> character + 128] = tree -> code;
		codeLengthTable[tree -> character + 128] = tree -> codeLength;
	}

	// Generate code recursively.
	generateCode(tree -> lChild, 0);
	generateCode(tree -> rChild, 1);

} // generateCode

// Desc: Traverse the tree and delete all nodes from the tree.
void HuffmanTree::deleteTree(HuffmanTreeNode *tree) {
	if (tree == NULL)
		return;
	deleteTree(tree -> lChild);
	deleteTree(tree -> rChild);
	delete tree;
	tree = NULL;
} // deleteTree

// Desc: Print the code of the given character.
void HuffmanTree::printCode(const char &c) const {
	unsigned length = codeLengthTable[c + 128];
	unsigned pos = 0x1 << (length - 1);
	for (unsigned i = 0; i < length; i++) {
		(pos & codeTable[c + 128]) == 0 ? cout << "0" : cout << "1";
		pos >>= 1;
	}
} // printCode

// Desc: Print the Huffman tree.
void HuffmanTree::display(HuffmanTreeNode *tree, bool stem[]) const {
	if (tree == NULL) {		// NULL internel vertex.
		cout << "NULL" << endl;
		return;
	}
	cout << "(";
	if (tree -> type == tree_node) {
		cout << "T, " << tree -> weight << ", " << tree -> code;
	} else {
		if (tree -> character >= 0x20 && tree -> character < 0x7F) {
			// Printable characters
			cout << "C, '" << tree -> character << "', " << tree -> weight << ", \"";
			printCode(tree -> character);
			cout << "\"";
		} else {
			cout << "C, ..., " << tree -> weight << ", \"";
			printCode(tree -> character);
			cout << "\"";
		}
	}
	cout << ")" << endl;

	// Leaf
	if (tree -> type == char_node)
		return;

	unsigned depth = 0;
	HuffmanTreeNode *ptr = tree;
	while (ptr -> parent != NULL) {
		depth++;
		ptr = ptr -> parent;
	}

	// Set the previous "stem" to false if "tree" is the 
	// left child of its parent. Otherwise, set it to true.
	if (depth > 0 && tree -> parent -> rChild == tree)
		stem[depth - 1] = true;
	else if (depth > 0 && tree -> parent -> lChild == tree)
		stem[depth - 1] = false;

	unsigned i = 0;
	while (i++ < depth) {
		if (stem[i - 1])
			cout << "    |  ";
		else
			cout << "       ";
	}
	cout << "    |--";
	display(tree -> rChild, stem);

	i = 0;
	while (i++ < depth) {
		if (stem[i - 1])
			cout << "    |  ";
		else
			cout << "       ";
	}
	cout << "    |--";
	display(tree -> lChild, stem);
} // display


// Public interfaces

// Desc: Constructor
HuffmanTree::HuffmanTree() {
	root = NULL;
	codeTable = new unsigned[256];
	codeLengthTable = new unsigned[256];
	for (int i = 0; i < 256; i++) {
		codeTable[i] = 0;
		codeLengthTable[i] = 0;
	}
} // Constructor

// Desc: Non-default constructor
HuffmanTree::HuffmanTree(PriorityQueue &pq) {
	root = NULL;
	codeTable = new unsigned[256];
	codeLengthTable = new unsigned[256];
	for (int i = 0; i < 256; i++) {
		codeTable[i] = 0;
		codeLengthTable[i] = 0;
	}
	createTree(pq);
} // Non-default constructor

// Desc: Destructor
HuffmanTree::~HuffmanTree() {
	deleteTree(root);
	delete [] codeTable;
	delete [] codeLengthTable;
} // Destructor

// Desc: Return the pointer of the code table.
unsigned *HuffmanTree::getCodeTable() const {
	return codeTable;
} // getCodeTable

// Desc: Return the pointer of the table that 
//       contains the length information of the code.
unsigned *HuffmanTree::getCodeLengthTable() const {
	return codeLengthTable;
} // getCodeLengthTable

// Desc: Return the height of the tree.
int HuffmanTree::getHeight(HuffmanTreeNode *tree) const {
	if (tree == NULL)
		return -1;
	int leftHeight = getHeight(tree -> lChild);
	int rightHeight = getHeight(tree -> rChild);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
} // getHeight

// Desc: Return the pointer that pointing to the root of tree.
HuffmanTreeNode *HuffmanTree::getRoot() const {
	return root;
} // getRoot


// Desc: Create a Huffman tree using a priority queue.
// Post: The priority queue is empty.
void HuffmanTree::createTree(PriorityQueue &pq) {

	HuffmanTreeNode *treeNode;

	if (pq.getLength() == 0) {

		// Empty file
		// Insert an empty node of type "tree_node".
		treeNode = new HuffmanTreeNode(tree_node, 0, NULL, NULL, NULL);
	} else if (pq.getLength() == 1) {

		// One-byte file
		HuffmanTreeNode *ptr = pq.peek();
		pq.dequeue();
		treeNode = new HuffmanTreeNode(
			tree_node, 
			ptr -> weight, 
			ptr, NULL, NULL
		);
	} else {
		
		// Multi-byte file
		while (pq.getLength() >= 2) {

			// Take two nodes with minimum weight.
			HuffmanTreeNode *ptr1 = pq.peek();
			pq.dequeue();
			HuffmanTreeNode *ptr2 = pq.peek();
			pq.dequeue();

			// Join them together.
			treeNode = new HuffmanTreeNode(
				tree_node, 
				ptr1 -> weight + ptr2 -> weight, 
				ptr1, ptr2, NULL
			);
			pq.enqueue(treeNode);	// Push it back to queue.
		}

		// The last element in the priority queue is the root.
		treeNode = pq.peek();
		pq.dequeue();
	}
	root = treeNode;
	generateCode(root, -1);
} // createTree


// Desc: Move one step from the given starting node.
//       direction:
//			Zero --> goto the left child 
//			Non-zero --> goto the right child
//  Pre: The given starting node exists.
// Post: Returns the pointer to the left or right child of the given node.
HuffmanTreeNode *HuffmanTree::walk(char direction, HuffmanTreeNode *startNode) const {
	if (direction == 0) {
		return startNode -> lChild;
	} else {
		return startNode -> rChild;
	}
} // walk

// Desc: Print the Huffman tree.
void HuffmanTree::display() const {
	int height = getHeight(root);
	if (height < 0)		// Empty tree
		return;
	bool *stem = new bool[height];
	display(root, stem);
	delete [] stem;
} // display

// End of HuffmanTree.cpp
