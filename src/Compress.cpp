/*
 * Compress.cpp
 *
 * Description: Implementation of compression function.
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
#include "HeaderFormat.h"

using namespace std;

// Desc: Write the required information to the header of 
//       the compressed file.
//       Implemented in "FileHeaderHandler.cpp".
int writeFileHeader(OutBitStream &, FrequencyCounter &);

// Desc: Compression function.
// Post: Return 0 if success. Otherwise, return -1.
int compress(const char *src, const char *dst) {

	cout << "Compressing ..." << endl;

	InBitStream in;		// Create an InBitStream object and open the source file.
	OutBitStream out;			// Create an OutBitStream object.
	FrequencyCounter counter;	// Frequency counter object
	PriorityQueue pq;			// Priority Queue

	// Prepare the source file.
	bool isSuccessful = in.openFile(src);
	if (isSuccessful == false) {
		cout << "Error: Cannot open file \"" << src << "\"." << endl;
		return -1;
	}

	counter.createTable(in);
	cout << src << " -> " << in.getFileSize() << " bytes" << endl;
	
	counter.createPriorityQueue(pq);	// Create Priority Queue.
	HuffmanTree huffTree(pq);			// Create Huffman Tree.
	// huffTree.display();

	in.openFile(src);	// Prepare the source file.

	// Create destination file.
	isSuccessful = out.openFile(dst);
	if (isSuccessful == false) {
		cout << "Error: Cannot create destination file \"" << dst << "\"." << endl;
		return -1;
	}

	// Write file header.
	unsigned totalHeaderSize = writeFileHeader(out, counter);

	// Load the data onto output buffer.
	// And write the compressed data to destination file.
	unsigned *codeTable = huffTree.getCodeTable();
	unsigned *codeLengthTable = huffTree.getCodeLengthTable();
	while (in.loadNextByte() == true) {
		out.loadNextByte(in.getCharacter(), codeTable, codeLengthTable);
	}
	out.sendEOF();	// Write the remaining bits (if any) to file.

	unsigned fileBodySize = out.getTotalNumOfBytes();

	// Write the original file size to file.
	out.writeValueAt(
		totalHeaderSize - ORIGINAL_SIZE, 
		in.getFileSize(), 
		ORIGINAL_SIZE
	);

	out.closeFile();	// Close file.

	cout << dst << " -> " << totalHeaderSize + fileBodySize << " bytes" << endl;

	if ((totalHeaderSize + fileBodySize) > in.getFileSize())
		cout << "*** Size of compressed file > size of source file ***" << endl;
	return 0;
} // compress

// End of Compress.cpp
