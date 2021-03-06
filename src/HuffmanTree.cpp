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
#include <string>

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

// Desc: Print the Huffman tree.
void HuffmanTree::display(HuffmanTreeNode *tree, bool drawBranch[]) const {
	// NULL internel vertex.
	if (tree == NULL) {
		cout << "NULL" << endl;
		return;
	} else {
		cout << tree << endl;	// Print the content of that node.
	}

	// Leaf node
	if (tree -> type == char_node)
		return;

	// Different types of branch.
	string branch1 = " |    ", branch2 = " |----", spaces = "      ";

	// Calculate the level of current node.
	int level = 0;
	HuffmanTreeNode *ptr = tree;
	while (ptr -> parent != NULL) {
		level++;
		ptr = ptr -> parent;
	}

	// Set the "drawBranch" of previous level to false if current node
	// is the left child of its parent. Otherwise, set it to true.
	if (level > 0 && tree -> parent -> rChild == tree)
		drawBranch[level - 1] = true;
	else if (level > 0 && tree -> parent -> lChild == tree)
		drawBranch[level - 1] = false;

	// Display right subtree.
	int count = 0;
	while (count++ < level) {
		if (drawBranch[count - 1])
			cout << branch1;
		else
			cout << spaces;
	}
	cout << branch2;
	display(tree -> rChild, drawBranch);

	// Display left subtree.
	count = 0;
	while (count++ < level) {
		if (drawBranch[count - 1])
			cout << branch1;
		else
			cout << spaces;
	}
	cout << branch2;
	display(tree -> lChild, drawBranch);

	// Draw gaps between siblings.
	if (level > 0 && tree -> parent -> rChild == tree) {
		for (int i = 0; i < level - 1; i++) {
			if (drawBranch[i])
				cout << branch1;
			else
				cout << spaces;
		}
		cout << branch1 << endl;
	}
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
	if (height < 0) {			// Empty tree
		cout << "NULL" << endl;
		return;
	} else {
		bool *drawBranch = new bool[height];
		display(root, drawBranch);
		delete [] drawBranch;
	}
} // display

// End of HuffmanTree.cpp
