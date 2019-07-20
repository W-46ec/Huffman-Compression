/*
 * PriorityQueue.cpp
 *
 * Description: Priority queue (heap) of type "HuffmanTreeNode* ".
 * Class Invariant: The element with smallest weight is on top of the heap. 
 *                  The maximum number of elements will not exceed 256.
 *
 *
 */

#include "PriorityQueue.h"

// Desc: Constructor
PriorityQueue::PriorityQueue() {
	capacity = MAX_SIZE;
	arr = new NodePtr[capacity];
	length = 0;
} // Constructor

// Desc: Non-default constructor
PriorityQueue::PriorityQueue(const PriorityQueue &pq) {
	capacity = pq.capacity;
	length = pq.length;
	arr = new NodePtr[capacity];

	for (int i = 0; i < length; i++) {
		arr[i] = pq.arr[i];
	}
} // Copy Constructor

// Desc: Destructor.
// Post: All elements are deallocated.
PriorityQueue::~PriorityQueue() {
	for (int i = 0; i < length; i++)
		delete arr[i];
	delete [] arr;
} // Destructor

// Desc: Returns true if priority queue is empty.
// Post: Priority queue remains unchanged.
bool PriorityQueue::isEmpty() const {
	return (length <= 0);
} // isEmpty

// Desc: Returns length of the priority queue.
// Post: Priority queue remains unchanged.
int PriorityQueue::getLength() const {
	return length;
} // getLength

// Desc: Heapifies the subtrees rooted at the given index.
//  Pre: The given index is a valid index.
//       Both its left and right subtrees are heaps.
void PriorityQueue::heapify(int index) {
	// Invalid index or leaf node.
	if (index < 0 || index > (length - 2) / 2 || length <= 1)
		return;

	int left = 2 * index + 1, right = 2 * index + 2, priorIdx = index;
	
	// Right child has higher priority.
	if (right < length && (*arr[right] < *arr[index]))
		priorIdx = right;

	// Left child has higher priority.
	if (*arr[left] < *arr[priorIdx])
		priorIdx = left;

	// One of the children has higher priority.
	if (priorIdx != index) {
		NodePtr tmp = arr[index];
		arr[index] = arr[priorIdx];
		arr[priorIdx] = tmp;
		heapify(priorIdx);
	}
} // heapify

// Desc: Trickle up the tree, so that the heap properties can be maintained.
void PriorityQueue::trickleUp(int index) {
	// Root node or invalid index.
	if (index <= 0 || index >= length)
		return;

	int parent = (index - 1) / 2;

	if (*arr[index] < *arr[parent]) {
		NodePtr tmp = arr[index];
		arr[index] = arr[parent];
		arr[parent] = tmp;
		trickleUp(parent);
	}
} // trickleUp

// Desc: Inserts element x into the priority queue.
// Post: The element is being inserted.
//       The length is increased by 1.
void PriorityQueue::enqueue(NodePtr &x) {
	arr[length++] = x;
	trickleUp(length - 1);
} // enqueue

// Desc: Removes an element from the top of the heap (extract min).
//  Pre: Priority queue is not empty.
// Post: The element with smallest weight is being removed from the heap.
//       The length is decreased by 1.
void PriorityQueue::dequeue() {
	if (!isEmpty()) {
		arr[0] = arr[--length];
		heapify(0);
	}
} // dequeue

// Desc: Returns the pointer to the tree node with the smallest weight.
//  Pre: Priority queue is not empty.
// Post: Priority queue remains unchanged.
NodePtr PriorityQueue::peek() const {
	return arr[0];
} // peek

// End of PriorityQueue.cpp
