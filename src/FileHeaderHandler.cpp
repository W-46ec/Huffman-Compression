/*
 * FileHeaderHandler.cpp
 *
 * Description: It provides methods to read / write the header
 *              of the compressed file.
 *
 *
 *
 */

#include "OutBitStream.h"
#include "FrequencyCounter.h"
#include "HeaderFormat.h"


// Desc: Write the required information to the header of the compressed file.
// Post: It returns the size of file-header (in bytes).
int writeFileHeader(OutBitStream &out, FrequencyCounter &counter) {

	// It's use for storing the size of file header.
	int totalHeaderSize = 0;

	// Bit flag, in the first byte of the compressed file.
	// To indicate some properties of the compressed file.
	char bit_flag = 0;

	// The size (number of bytes) of one single value from frequency table.
	unsigned valueSize;

	// It's the least significant bit of bit_flag, can be either 0 or 1.
	// 		0: Frequency table will be written as some (key, value) pairs.
	// 		1: Frequency table will be written as 256 consecutive values (weight).
	char compressionMode;

	// The maximum weight.
	unsigned maxWeight = counter.getMaxWeight();

	// Frequency information from the FrequencyCounter object.
	unsigned *bitVector = counter.getBitVector();

	// Dictionary size: the number of different characters in frequency table.
	unsigned dictionarySize = counter.getSize();

	// Decide the compression mode (key-value pair or list mode)
	// And the size of value (valueSize: 1, 2, or 4 bytes)
	if (maxWeight <= 255) {

		// All weights are under 1 byte.
		// Use 1 byte as value size.
		valueSize = CHAR_VALUE_SIZE;
		bit_flag = 0x0;
		if (dictionarySize <= 127) {
			// When 1 + (1 + 1) * dictionarySize < 256 * 1, 
			// Using key-value pair mode would be less space consuming.
			compressionMode = 0x0;	// key-value pair mode
		} else {
			// Otherwise, listing all 256 weights (value) would be
			// less space consuming.
			compressionMode = 0x1;	// list mode
		}
	} else if (maxWeight <= 65535) {

		// All weights are under 2 bytes.
		// Use 2 bytes as value size.
		valueSize = SHORT_VALUE_SIZE;
		bit_flag = 0x2;
		if (dictionarySize <= 170) {
			// When 1 + (1 + 2) * dictionarySize < 256 * 2, 
			// Using key-value pair mode would be less space consuming.
			compressionMode = 0x0;	// key-value pair mode
		} else {
			// Otherwise, listing all 256 weights (value) would be
			// less space consuming.
			compressionMode = 0x1;	// list mode
		}
	} else {

		// Some weights exceed 2 bytes.
		// Use 4 bytes as value size.
		valueSize = UNSIGNED_VALUE_SIZE;
		bit_flag = 0x4;
		if (dictionarySize <= 204) {
			// When 1 + (1 + 4) * dictionarySize < 256 * 4, 
			// Using key-value pair mode would be less space consuming.
			compressionMode = 0x0;	// key-value pair mode
		} else {
			// Otherwise, listing all 256 weights (value) would be
			// less space consuming.
			compressionMode = 0x1;	// list mode
		}
	}
	
	// Write the bit flag to the beginning of the file.
	bit_flag += compressionMode;
	out.writeByte(bit_flag);
	totalHeaderSize += BIT_FLAG;

	// Write the frequency table to the destination file.
	if (compressionMode == 0) {		// key-value pair mode

		// Write the size of frequency table to the destination file.
		out.writeValue(dictionarySize, HEADER_BODY_SIZE_BYTE);
		totalHeaderSize += HEADER_BODY_SIZE_BYTE;

		// Format: [dictionary size][dictionary size * (key, value)]
		for (int i = 0; i < 256; i++) {
			if (bitVector[i] != 0) {
				out.writeByte(i - 128);		// Character
				out.writeValue(bitVector[i], valueSize);	// weight
			}
		}
	} else {	// list mode

		// Format: [256 consecutive values]
		for (int i = 0; i < 256; i++) {
			out.writeValue(bitVector[i], valueSize);
		}
	}

	if (compressionMode == 0) {
		// Key-value pair mode Format: 
		// [dictionary size][dictionary size * (key, value)]
		totalHeaderSize += (KEY_SIZE + valueSize) * dictionarySize;
	} else {
		// Key-value pair mode Format: 
		// [256 consecutive values]
		totalHeaderSize += valueSize * 256;
	}

	// 4 bytes are preserved for indicating the file body size.
	out.writeValue(0, ORIGINAL_SIZE);
	totalHeaderSize += ORIGINAL_SIZE;


	// Return the header size of the compressed file.
	return totalHeaderSize;
}

// Desc: Read the information from the header of the compressed file.
// Post: It returns the size of file-header (in bytes).
int readFileHeader(InBitStream &in, FrequencyCounter &counter) {

	// It's use for storing the size of file header.
	int totalHeaderSize = 0;

	// Bit flag, in the first byte of the compressed file.
	// To indicate some properties of the compressed file.
	char bit_flag = 0;

	// The size (number of bytes) of one single value from frequency table.
	unsigned valueSize;

	// It's the least significant bit of bit_flag, can be either 0 or 1.
	// 		0: Frequency table will be written as (key, value) pairs.
	// 		1: Frequency table will be written as 256 consecutive values.
	char compressionMode;

	// // The maximum weight.
	// unsigned maxWeight = counter.getMaxWeight();

	// Frequency information.
	unsigned *bitVector = new unsigned[256];
	for (int i = 0; i < 256; i++)	// Clear the random data.
		bitVector[i] = 0;

	// Dictionary size: the number of different character in frequency table.
	unsigned dictionarySize = 0;


	in.loadNextByte();
	bit_flag = in.getCharacter();
	totalHeaderSize++;

	compressionMode = bit_flag & 0x1;	// Get the least significant bit of bit flag.

	valueSize = (((unsigned)bit_flag) & 0x6);	// Get last second and last third bits.

	if (valueSize == 0x0) {		// value size is 1 byte.
		valueSize = CHAR_VALUE_SIZE;
	} else if (valueSize == 0x2) {	// value size is 2 bytes.
		valueSize = SHORT_VALUE_SIZE;
	} else {	// value size is 4 bytes.
		valueSize = UNSIGNED_VALUE_SIZE;
	}

	if (compressionMode == 0x0) {	// key-value pair mode.
		char key;
		unsigned value;

		// Read the dictionary size (The number of key-value pairs).
		dictionarySize = in.readValue(HEADER_BODY_SIZE_BYTE);
		totalHeaderSize++;

		for (unsigned i = 0; i < dictionarySize; i++) {
			in.loadNextByte();
			key = in.getCharacter();
			value = in.readValue(valueSize);
			bitVector[key + 128] = value;
		}
		totalHeaderSize += dictionarySize * (KEY_SIZE + valueSize);
	} else {
		unsigned value;
		for (unsigned i = 0; i < 256; i++) {
			value = in.readValue(valueSize);
			bitVector[i] = value;
		}
		totalHeaderSize += 256 * valueSize;
	}

	// Restore the frequency table using a bit vector.
	counter.restoreTable(bitVector);

	delete [] bitVector;

	return totalHeaderSize;
}

// End of FileHeaderHandler.cpp
