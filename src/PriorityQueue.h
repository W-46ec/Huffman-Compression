/*
 * PriorityQueue.cpp
 *
 * Description: Priority queue (heap) of type "HuffmanTreeNode* ".
 * Class Invariant: The element with smallest weight is on top of the heap. 
 *                  The maximum number of elements will not exceed 256.
 *
 *
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "HuffmanTreeNode.h"


typedef HuffmanTreeNode* NodePtr;

class PriorityQueue {

	private:

		// Since there are only 256 different possibles, and each time
		// we enqueue, we need to dequeue 2 elements. Therefore, 
		// the number of element will never exceed 256.
		static const int MAX_SIZE = 256;
		NodePtr *arr;
		int length;
		int capacity;

		// Desc: Heapifies the subtrees rooted at the given index.
		//  Pre: The given index is a valid index.
		//       Both its left and right subtrees are heaps.
		void heapify(int index);

		// Desc: Trickle up the tree, so that the heap properties can be maintained.
		void trickleUp(int index);

	public:

		// Desc: Default Constructor.
		PriorityQueue();

		// Desc: Copy Constructor.
		PriorityQueue(const PriorityQueue &pq);

		// Desc: Destructor.
		// Post: All elements are deallocated.
		~PriorityQueue();

		// Desc: Returns true if priority queue is empty.
		// Post: Priority queue remains unchanged.
		bool isEmpty() const;

		// Desc: Returns length of the priority queue.
		// Post: Priority queue remains unchanged.
		int getLength() const;

		// Desc: Inserts element x into the priority queue.
		// Post: The element is being inserted.
		//       The length is increased by 1.
		void enqueue(NodePtr &x);

		// Desc: Removes an element from the top of the heap (extract min).
		//  Pre: Priority queue is not empty.
		// Post: The element with smallest weight is being removed from the heap.
		//       The length is decreased by 1.
		void dequeue();

		// Desc: Returns a pointer to the tree node with the smallest weight.
		//  Pre: Priority queue is not empty.
		// Post: Priority queue remains unchanged.
		NodePtr peek() const;

}; // PriorityQueue

#endif

 // End of PriorityQueue.h

