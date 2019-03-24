/*
 * PriorityQueue.cpp
 *
 * Description: Circular priority queue of type "HuffmanTreeNode *"."
 * Class Invariant: The priority queue is sorted.
 *                  The element with smallest weight is in the "front" of the queue. 
 *                  The maximum number of element will not exceed 256.
 *
 *
 */

#include "PriorityQueue.h"

// Desc: Constructor
PriorityQueue::PriorityQueue() {
	capacity = MAX_SIZE;
	arr = new NodePtr[capacity];
	length = 0;
	frontIndex = 0;
	backIndex = 0;
} // Constructor

// Desc: Non-default constructor
PriorityQueue::PriorityQueue(const PriorityQueue &pq) {
	capacity = pq.capacity;
	length = pq.length;
	frontIndex = pq.frontIndex;
	backIndex = pq.backIndex;
	arr = new NodePtr[capacity];

	for (int i = 0; i < capacity; i++) {
		arr[i] = pq.arr[i];
	}
} // Copy Constructor

// Destructor
PriorityQueue::~PriorityQueue() {
	if (!isEmpty()) {
		for (int i = 0; i < length; i++) {
			delete arr[(frontIndex + i) % capacity];
		}
	}
	delete [] arr;
} // Destructor

// Desc: Returns true if Priority Queue empty.
	// Post: Priority Queue remains unchanged.
bool PriorityQueue::isEmpty() const {
	return (length == 0);
} // isEmpty

// Desc: Returns length of the Priority Queue.
	// Post: Priority Queue remains unchanged.
int PriorityQueue::getLength() const {
	return length;
} // getLength

// Desc: Inserts x in sorted order.
//  Pre: Priority Queue is sorted.
// Post: Priority Queue remains sorted.
//       The length is increment by 1.
//       The backIndex is increment by 1.
void PriorityQueue::enqueue(NodePtr &x) {

	// Search from the back.
	int currentIdx = backIndex;

	// Plus a "capacity" to avoid getting a negative index
	int previousIdx = (currentIdx + capacity - 1) % capacity;

	while (currentIdx != frontIndex && (*x) < *(arr[previousIdx])) {
		arr[currentIdx] = arr[previousIdx];
		currentIdx = previousIdx;
		previousIdx = (currentIdx + capacity - 1) % capacity;
	}

	arr[currentIdx] = x;
	length++;
	backIndex = (backIndex + 1) % capacity;

} // enqueue


// Desc: Removes one element from the "front" of the queue.
//  Pre: Priority Queue not empty.
// Post: The element with smallest weight is being removed from the queue.
//       The length is decrement by 1.
void PriorityQueue::dequeue(){

	// Remove from the front
	frontIndex = (frontIndex + 1) % capacity;
	length--;
} // dequeue


// Desc: Returns the pointer to the tree node with the smallest weight.
//  Pre: Priority Queue not empty.
// Post: Priority Queue is unchanged.
NodePtr PriorityQueue::peek() const {
	return arr[frontIndex];
} // peek

// End of PriorityQueue.cpp
