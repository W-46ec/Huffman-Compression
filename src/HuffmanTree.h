/*
 * HuffmanTree.h
 *
 * Description: HuffmanTree class
 *
 *
 *
 */

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanTreeNode.h"
#include "PriorityQueue.h"

class HuffmanTree {
private:
	HuffmanTreeNode *root;			// root
	unsigned *codeTable;
	unsigned *codeLengthTable;

	// Helper function

	// Desc: Traverse the Huffman tree and generate code for each node.
	//  Pre: "direction" is one of 0, 1, or -1.
	//       	 0: current tree node is the left child of the parent node;
	//       	 1: current tree node is the right child of the parent node;
	//       	-1: current tree node is the root (parent == NULL);
	void generateCode(HuffmanTreeNode *tree, int direction);

	// Desc: Traverse the tree and delete all nodes from the tree.
	void deleteTree(HuffmanTreeNode *tree);

	// Desc: Print the Huffman tree.
	void display(HuffmanTreeNode *tree, bool drawBranch[]) const;

public:

	// Constructors and destructor
	HuffmanTree();
	HuffmanTree(PriorityQueue &pq);
	~HuffmanTree();

	// Desc: Return the pointer of the code table.
	unsigned *getCodeTable() const;

	// Desc: Return the pointer of the table that 
	//       contains the length information of the code.
	unsigned *getCodeLengthTable() const;

	// Desc: Return the height of the given tree.
	//       If tree is empty, return -1;
	int getHeight(HuffmanTreeNode *tree) const;

	// Desc: Return the pointer that pointing the root of the tree.
	HuffmanTreeNode *getRoot() const;

	// Desc: Create a Huffman tree using a priority queue.
	// Post: The priority queue is empty.
	void createTree(PriorityQueue &pq);

	// Desc: Move one step from the given starting node.
	//       char direction:
	//			Zero --> goto the left child 
	//			Non-zero --> goto the right child
	//  Pre: The given starting node exists.
	// Post: Returns the pointer to the left or right child of the given node.
	HuffmanTreeNode *walk(char direction, HuffmanTreeNode *startNode) const;

	// Desc: Print the Huffman tree.
	void display() const;

}; // HuffmanTree

#endif

// End of HuffmanTree.h
