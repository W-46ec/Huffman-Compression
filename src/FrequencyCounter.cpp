/*
 * FrequencyCounter.cpp
 *
 * Description: It provides interface to count the frequency of elements. 
 *
 *
 *
 */

#include "FrequencyCounter.h"
#include "InBitStream.h"
#include "HuffmanTreeNode.h"
#include "PriorityQueue.h"


// Desc: Default constructor
FrequencyCounter::FrequencyCounter() {
	size = 0;
	bitVector = new unsigned[256];
	for (int i = 0; i < 256; i++) {
		bitVector[i] = 0;
	}
} // Default constructor

// Desc: Non-default constructor
FrequencyCounter::FrequencyCounter(const FrequencyCounter &counter) {
	size = counter.size;
	bitVector = new unsigned[256];
	for (int i = 0; i < 256; i++) {
		bitVector[i] = counter.bitVector[i];
	}
} // Non-default constructor

// Desc: Destructor
FrequencyCounter::~FrequencyCounter() {
	delete [] bitVector;
} // Destructor

// Desc: Return the number of different characters in the frequency table.
unsigned FrequencyCounter::getSize() const {
	return size;
} // getSize

// Desc: Return the character with maximum weight.
char FrequencyCounter::getMaxChar() const {
	int maxIdx = 0;
	for (int i = 0; i < 256; i++) {
		maxIdx = bitVector[i] > bitVector[maxIdx] ? i : maxIdx;
	}
	return (maxIdx - 128);
} // getMaxChar


// Desc: Return the maximum weight.
unsigned FrequencyCounter::getMaxWeight() const {
	return (size == 0 ? 0 : bitVector[getMaxChar() + 128]);
} // getMaxWeight

// Desc: Return the pointer to bit vector.
unsigned *FrequencyCounter::getBitVector() {
	return bitVector;
} // getBitVector

// Desc: Read data from the file and create the frequency table.
void FrequencyCounter::createTable(InBitStream &in) {

	// Count the frequencies.
	while (in.loadNextByte() == true) {
		if (bitVector[in.getCharacter() + 128] == 0)
			size++;
		bitVector[in.getCharacter() + 128]++;
	}

} // createTable

// Desc: Restore the table using a bit vector.
void FrequencyCounter::restoreTable(const unsigned *table) {

	// Restore the frequency table.
	for (int i = 0; i < 256; i++) {
		bitVector[i] = table[i];
		if (table[i] != 0)
			size++;
	}

} // restoreTable

// Desc: Push the frequency information into a priority queue.
void FrequencyCounter::createPriorityQueue(PriorityQueue &pq) {
	for (int i = 0; i < 256; i++) {
		if (bitVector[i] != 0) {
			// (type, weight, character)
			HuffmanTreeNode *nodePtr = new HuffmanTreeNode(char_node, bitVector[i], i - 128);
			pq.enqueue(nodePtr);
		}
	}
} // createPriorityQueue

// End of FrequencyCounter.cpp
