/*
 * HeaderFormat.h
 *
 * Description: This file specifies details about the 
 *              header format of the compressed file.
 *
 *
 *
 */


// Bit flag, the first byte of the compressed file.
// To indicate some properties of the compressed file.
// Indices: [7, 6, 5, 4, 3, 2, 1, 0]
// Bit 0: Freq table storage mode.
// 			0: key-value pair mode
//             Format: [dictionary size][dictionary size * (key, value)]
// 			1: list mode
//             Format: [256 consecutive values]
// Bit 2 & 1: Value Size (The number of bytes of each value).
// 			00: char 		1 byte
// 			01: short 		2 bytes
// 			10: unsigned 	4 bytes
// Bit 7 - 3: Unused.
const unsigned BIT_FLAG = 1;

// Indicate the size of header-body, which is the dictionary 
// size (the number of key-value pairs).
// It is used only in key-value pair mode (compression mode == 0).
const unsigned HEADER_BODY_SIZE_BYTE = 1;


// Size of key in frequency table.
const unsigned KEY_SIZE = 1;


// Sizes of values in frequency table.
// It may vary, depends on how big is the biggest weight.
const unsigned CHAR_VALUE_SIZE = 1;
const unsigned SHORT_VALUE_SIZE = 2;
const unsigned UNSIGNED_VALUE_SIZE = 4;


// At the end of file headder.
// Uses 4 bytes to indicate the size of the original file.
const unsigned ORIGINAL_SIZE = 4;

// End of HeaderFormat.h
