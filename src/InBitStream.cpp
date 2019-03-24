/*
 * InBitStream.cpp
 *
 * Description: It provides methods to read data from the file. 
 *
 *
 *
 */

#include "InBitStream.h"

#include <fstream>

using namespace std;

// Desc: Constructor
InBitStream::InBitStream() {
	fileSize = 0;
	isOpen = false;
	buffer = new char(0);	// Initialize to 0
} // Default constructor

// Desc: Non-default constructor
InBitStream::InBitStream(const char *fileName) {
	fileSize = 0;
	isOpen = false;
	buffer = new char(0);	// Initialize to 0
	this -> openFile(fileName);
} // Non-default constructor

// Desc: Destructor
InBitStream::~InBitStream() {
	if (isOpen == true)
		fin.close();
	delete buffer;
} // Destructor


// Desc: Open a file and return the status.
// Post: If it is opened successfully, return true.
//       Otherwise, return false.
bool InBitStream::openFile(const char *fileName) {
	this -> fileSize = 0;
	if (this -> isOpen == true)
		fin.close();
	(this -> fin).open(fileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		isOpen = false;
	} else {
		isOpen = true;
	}
	return this -> isOpen;
} // openFile


// Desc: Read one byte from the file and store it in *buffer
// Post: "isOpen" is set to false if it reach the end of file.
bool InBitStream::loadNextByte() {
	if (fin) {
		fin.read(buffer, 1);
		if (fin) {
			fileSize++;
			return true;
		}
	}
	fin.close();
	isOpen = false;
	return false;
} // loadNextByte


// Desc: Read "valueSize" bytes data from the file,
//       and then convert it to an unsigned value.
//  Pre: File is not empty.
unsigned InBitStream::readValue(const unsigned valueSize) {
	unsigned value = 0;
	fin.read((char *)&value, valueSize);
	return value;
} // readValue


// Desc: Move the file pointer to the given position.
// Post: The file pointer is "offset" bytes away from the beginning of the file.
void InBitStream::gotoPos(const unsigned offset) {
	fin.seekg(offset, ios::beg);
} // gotoPos


// Desc: Return the value in buffer.
char InBitStream::getCharacter() const {
	return buffer[0];
} // getCharacter


// Desc: Returns the number of bytes of the file.
//       It returns the correct value only after
//       finishing reading the whole file.
unsigned InBitStream::getFileSize() const {
	return fileSize;
} // getFileSize


// End of InBitStream.cpp
