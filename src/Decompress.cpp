/*
 * Decompress.cpp
 *
 * Description: Implementation of decompression function.
 *
 *
 *
 */

#include <iostream>
#include "InBitStream.h"
#include "OutBitStream.h"
#include "FrequencyCounter.h"
#include "PriorityQueue.h"
#include "HuffmanTree.h"
#include "HuffmanTreeNode.h"
#include "HeaderFormat.h"

using namespace std;

// Desc: Read the needed information from the header of 
//       the compressed file.
//       Implemented in "FileHeaderHandler.cpp".
int readFileHeader(InBitStream &, FrequencyCounter &);


// Desc: Decompression function.
// Post: Return 0 if success. Otherwise, return -1.
int decompress(const char *src, const char *dst) {

	cout << "Decompressing ... " << endl;

	InBitStream in;				// Create an InBitStream object and open the source file.
	OutBitStream out;			// Create an OutBitStream object.
	FrequencyCounter counter;	// Frequency counter object
	PriorityQueue pq;			// Priority Queue

	bool isSuccessful = in.openFile(src);
	if (isSuccessful == false) {
		cout << "Error: Cannot open file \"" << src << "\"." << endl;
		return -1;
	}

	// Read file header.
	unsigned totalHeaderSize = readFileHeader(in, counter);

	counter.createPriorityQueue(pq);	// Create Priority Queue.
	HuffmanTree huffTree(pq);			// Create Huffman Tree.

	// Read the file-body size.
	unsigned originalFileSize = in.readValue(ORIGINAL_SIZE);
	totalHeaderSize += ORIGINAL_SIZE;

	in.openFile(src);	// Prepare the source file.

	// Create destination file.
	isSuccessful = out.openFile(dst);
	if (isSuccessful == false) {
		cout << "Error: Cannot create destination file \"" << dst << "\"." << endl;
		return -1;
	}

	// Move the read pointer to the beginning of file-body.
	in.gotoPos(totalHeaderSize);

	unsigned processedChar = 0;
	HuffmanTreeNode *ptr = huffTree.getRoot();	// Used for search the code.

	while (processedChar < originalFileSize) {
		if (in.loadNextByte() == true) {
			char buffer = 0;		// "0000 0000"
			short bitMask = 0x80;	// "1000 0000"
			buffer = in.getCharacter();	// Read one byte from the file.

			// 8 bits in one byte.
			for (int i = 0; i < 8; i++) {
				// Get the direction.
				char direction = buffer & bitMask;

				// Move one step on the Huffman tree.
				ptr = huffTree.walk(direction, ptr);

				// Untill it reach NULL (Might happen in empty file), 
				// or a character node.
				if (ptr != NULL && ptr -> type == char_node) {

					// Write the corresponding character to the destination file.
					out.writeByte(ptr -> character);
					ptr = huffTree.getRoot();	// Reset the pointer
					processedChar++;
					if (processedChar >= originalFileSize) {

						// It may occur when the last byte of file
						// has some padding 0's.
						break;
					}
				}
				bitMask >>= 1;
			}
		} else {

			cout << "Error: \"" << src << "\" is corrupted." << endl;
			out.closeFile();
			return -1;
		}
	}

	// Close the destination file.
	out.closeFile();

	cout << "Completed: " << src << " -> " << dst << endl;
	return 0;
	
} // deconpress

// End of Decompress.cpp
