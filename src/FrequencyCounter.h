/*
 * FrequencyCounter.h
 *
 * Description: It provides interface to count the frequency of elements. 
 *
 *
 *
 */

#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H

#include "InBitStream.h"
#include "PriorityQueue.h"

class FrequencyCounter {
private:
	unsigned *bitVector;	// Bit vector

	// The number of different characters in the frequency table.
	unsigned size;

public:

	// Constructors and destructor
	FrequencyCounter();
	FrequencyCounter(const FrequencyCounter &counter);
	~FrequencyCounter();

	// Desc: Return the number of different characters in the frequency table.
	unsigned getSize() const;

	// Desc: Return the character with maximum weight.
	char getMaxChar() const;

	// Desc: Return the maximum weight.
	unsigned getMaxWeight() const;

	// Desc: Return the pointer to bit vector.
	unsigned *getBitVector();
	
	// Desc: Read data from the file and create the frequency table.
	void createTable(InBitStream &in);

	// Desc: Restore the table using a bit vector.
	void restoreTable(const unsigned *table);

	// Desc: Push the frequency information into a priority queue.
	void createPriorityQueue(PriorityQueue &pq);
	
}; // FrequencyCounter

#endif

// End of FrequencyCounter.h
