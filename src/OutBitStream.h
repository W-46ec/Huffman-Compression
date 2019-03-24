/*
 * OutBitStream.h
 *
 * Description: It provides methods to write data to the file. 
 *
 *
 *
 */

#ifndef OUTBITSTREAM_H
#define OUTBITSTREAM_H

#include <fstream>

using namespace std;

class OutBitStream {
private:
	ofstream fout;				// ofstream object
	char *buffer;				// Used for storing the data temporarily.
	short bitMask;				// bitMask
	unsigned totalNumOfBytes;	// Number of bytes processed.
public:

	// Constructors and Destructor
	OutBitStream();
	OutBitStream(const char *fileName);
	~OutBitStream();

	// Desc: Open the destination file.
	// Post: If it is opened successfully, return true.
	//       Otherwise, return false.
	bool openFile(const char *fileName);

	// Desc: Write the remaining bits (if any) in the buffer to file
	//       and close the destination file.
	void closeFile();

	// Desc: Write the remaining bits (if any) in the buffer to file.
	void sendEOF();

	// Desc: Find the code for the given character and 
	//       write the code to the buffer.
	// Post: If buffer is full, its data will be written to the
	//       destination file and buffer will be reset.
	void loadNextByte(const char &c, unsigned *codeTable, unsigned *codeLengthTable);

	// Desc: Write one byte to the file.
	void writeByte(const char &data);

	// Desc: Write one byte to the file at the given position.
	void writeByteAt(const unsigned offset, const char &data);

	// Desc: Convert the value to a "valueSize" bytes data chunk
	//       and write it to the file.
	void writeValue(unsigned value, const unsigned valueSize);

	// Desc: Convert the value to a "valueSize" bytes data chunk
	//       and write it to the file at the given position.
	// Post: The file pointer is pointing to the end of the file.
	void writeValueAt(const unsigned offset, unsigned value, const unsigned valueSize);

	// Desc: Returns the number of bytes that have been written to the destination file.
	unsigned getTotalNumOfBytes() const;
	
}; // OutBitStream

#endif

// End of OutBitStream.h
