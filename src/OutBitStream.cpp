/*
 * OurBitStream.cpp
 *
 * Description: It provides methods to write data to the file. 
 *
 *
 *
 */

#include <iostream>
#include "OutBitStream.h"

using namespace std;

// Desc: Default constructor
OutBitStream::OutBitStream() {
	totalNumOfBytes = 0;
	bitMask = 0x80;			// "1000 0000"
	buffer = new char(0);	// Initialize to 0
} // Default constructor

// Desc: Non-default constructor
OutBitStream::OutBitStream(const char *fileName) {
	totalNumOfBytes = 0;
	bitMask = 0x80;			// "1000 0000"
	buffer = new char(0);	// Initialize to 0
	openFile(fileName);
} // Non-default constructor

// Desc: Destructor
OutBitStream::~OutBitStream() {
	delete buffer;
} // destructor


// Desc: Open the destination file.
// Post: If it is opened successfully, return true.
//       Otherwise, return false.
bool OutBitStream::openFile(const char *fileName) {
	this -> totalNumOfBytes = 0;
	if (fout.is_open() == true)
		fout.close();
	(this -> fout).open(fileName, ios::out | ios::binary);
	if (!fout.is_open()) {
		return false;
	} else {
		return true;
	}
} // openFile


// Desc: Write the remaining bits (if any) in the buffer to file
//       and close the destination file.
void OutBitStream::closeFile() {
	sendEOF();	// Write the remained bits (if any) to file.
	fout.close();
} // closeFile

// Desc: Write the remaining bits (if any) in the buffer to file.
void OutBitStream::sendEOF() {
	// Write the remaining bits (if any) to file.
	if (bitMask != 0x80) {
		fout.write(buffer, 1);
		totalNumOfBytes++;
							// Reset the buffer and bitMask.
		bitMask = 0x80;		// "1000 0000"
		*buffer = 0;		// "0000 0000"
	}
} // sendEOF


// Desc: Find the code for the given character and 
//       write the code to the buffer.
// Post: If buffer is full, its data will be written to the
//       destination file and buffer will be reset.
void OutBitStream::loadNextByte(const char &c, unsigned *codeTable, unsigned *codeLengthTable) {
	unsigned code = codeTable[c + 128];
	unsigned codeLength = codeLengthTable[c + 128];
	unsigned pos = 0x1 << (codeLength - 1);
	for (unsigned i = 0; i < codeLength; i++) {
		if ((code & pos) != 0)
			*buffer = (*buffer) | bitMask;
		bitMask >>= 1;			// Right shift
		pos >>= 1;

		if (bitMask == 0x0) {	// Buffer is full.
			fout.write(buffer, 1);
			totalNumOfBytes++;
								// Reset the buffer and bitMask.
			bitMask = 0x80;		// "1000 0000"
			*buffer = 0x0;		// "0000 0000"
		}
	}
} // loadNextByte

// Desc: Write one byte to the file.
void OutBitStream::writeByte(const char &data) {
	fout.write(&data, 1);
} // writeByte

// Desc: Write one byte to the file at the given position.
void OutBitStream::writeByteAt(const unsigned offset, const char &data) {
	fout.seekp(offset, ios::beg);
	fout.write(&data, 1);
	fout.seekp(0, ios::end);
} // writeByteAt

// Desc: Convert the value to a "valueSize" bytes data chunk
//       and write it to the file.
void OutBitStream::writeValue(unsigned value, const unsigned valueSize) {
	fout.write((char *)&value, valueSize);
} // writeValue

// Desc: Convert the value to a "valueSize" bytes data chunk
//       and write it to the file at the given position.
// Post: The file pointer is pointing to the end of the file.
void OutBitStream::writeValueAt(const unsigned offset, unsigned value, const unsigned valueSize) {
	fout.seekp(offset, ios::beg);
	fout.write((char *)&value, valueSize);
	fout.seekp(0, ios::end);
} // writeValueAt

// Desc: Returns the number of bytes that have been written to the destination file.
unsigned OutBitStream::getTotalNumOfBytes() const {
	return totalNumOfBytes;
} // getTotalNumOfBytes

// End of OutBitStream.cpp
