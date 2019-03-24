/*
 * InBitStream.h
 *
 * Description: It provides methods to read data from the file. 
 *
 *
 *
 */

#ifndef INBITSTREAM_H
#define INBITSTREAM_H

#include <fstream>

using namespace std;

class InBitStream {
private:
	ifstream fin;		// ifstream object
	char *buffer;		// Used for storing the data temporarily.
	bool isOpen;		// Indicate the status of the file.
	unsigned fileSize;	// File size
public:

	// Constructors and Destructor
	InBitStream();
	InBitStream(const char *fileName);
	~InBitStream();

	// Desc: Open a file and return the status.
	// Post: If it is opened successfully, return true.
	//       Otherwise, return false.
	bool openFile(const char *fileName);

	// Desc: Read one byte from the file and store it in *buffer
	// Post: "isOpen" is set to false if it reach the end of file.
	bool loadNextByte();

	// Desc: Read "valueSize" bytes data from the file,
	//       and then convert it to an unsigned value.
	//  Pre: File is not empty.
	unsigned readValue(const unsigned valueSize);

	// Desc: Move the file pointer to the given position.
	// Post: The file pointer is "offset" bytes away from the beginning of the file.
	void gotoPos(const unsigned offset);

	// Desc: Return the value in buffer.
	char getCharacter() const;

	// Desc: Returns the number of bytes of the file.
	//       It returns the correct value only after
	//       finishing reading the whole file.
	unsigned getFileSize() const;
	
}; // InBitStream

#endif

// End of InBitStream.h

