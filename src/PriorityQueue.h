/*
 * PriorityQueue.h
 *
 * Description: Circular priority queue of type "HuffmanTreeNode *"."
 * Class Invariant: The priority queue is sorted.
 *                  The element with smallest weight is in the "front" of the queue. 
 *                  The maximum number of element will not exceed 256.
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
		int frontIndex, backIndex;

	public:
		
		// Desc: Default Constructor.
		// Post: head is NULL and length is 0
		PriorityQueue();


		// Desc: Copy Constructor.
		PriorityQueue(const PriorityQueue &pq);


		// Desc: Destructor.
		// Post: All elements are deallocated.
		~PriorityQueue();


		// Desc: Returns true if Priority Queue empty.
		// Post: Priority Queue remains unchanged.
		bool isEmpty() const;


		// Desc: Returns length of the Priority Queue.
		// Post: Priority Queue remains unchanged.
		int getLength() const;


		// Desc: Inserts x in sorted order.
		//  Pre: Priority Queue is sorted.
		// Post: Priority Queue remains sorted.
		//       The length is increment by 1.
		//       The backIndex is increment by 1.
		void enqueue(NodePtr &x);
	

		// Desc: Removes one element from the "front" of the queue.
		//  Pre: Priority Queue not empty.
		// Post: The element with smallest weight is being removed from the queue.
		//       The length is decrement by 1.
		void dequeue();


		// Desc: Returns the pointer to the tree node with the smallest weight.
		//  Pre: Priority Queue not empty.
		// Post: Priority Queue is unchanged.
		NodePtr peek() const;

}; // PriorityQueue

#endif

 // End of PriorityQueue.h

