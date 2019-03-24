/*
 * main.cpp
 *
 * Description: main function.
 *
 *
 *
 */

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Desc: Prototypes
//       Compression and Decompression functions.
//       Implemented in "Compress.cpp" and "Decompress.cpp" repectively.
int compress(const char *src, const char *dst);
int decompress(const char *src, const char *dst);

// Desc: display the usage of the program.
void helpMessage() {
	cout << "Usage:\t" << "[-options] [Source] [Destination]" << endl;
	cout << "Options:\t-c, --compress" << "\t\t" << "Compress the input file and write the compressed data to the destination file." << endl;
	cout << "\t\t-d, --decompress" << "\t" << "Decompress the input file and write the decompressed data to the destination file." << endl;
	cout << "\t\t-h, --help" << "\t\t" << "Display this information." << endl;
}

// Desc: main function
int main(int argc, char *argv[]) {

	if (argc == 2) {
		string option = argv[1];
		if (option == "-h" || option == "--help") {
			helpMessage();
			return 0;
		} else if (option == "-c" || option == "-d" || option == "--compress" || option == "--decompress") {
			cout << "Error: Invalid number of arguments." << endl;
			helpMessage();
			return 1;
		} else {
			cout << "Error: Unrecognized option \'" << option << "\'." << endl;
			helpMessage();
			return 1;
		}
	} else if (argc == 4) {
		string option = argv[1];
		string src = argv[2];
		string dst = argv[3];

		if (option == "-c" || option == "--compress") {		// Compression
			if (src != dst){
				clock_t start = clock();
				int status = compress(argv[2], argv[3]);
				if (status == -1) {
					return -1;
				} else {
					cout << "Compression completed in " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " seconds." << endl;
					return 0;
				}
			} else {
				cout << "Error: Source and destination file names are the same." << endl;
				return 1;
			}
		} else if (option == "-d" || option == "--decompress") {	// Decompression
			if (src != dst){
				clock_t start = clock();
				int status = decompress(argv[2], argv[3]);
				if (status == -1) {
					return -1;
				} else {
					cout << "Decompression completed in " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " seconds." << endl;
					return 0;
				}
			} else {
				cout << "Error: Source and destination file names are the same." << endl;
				return 1;
			}
		} else {
			cout << "Error: Unrecognized option \'" << option << "\'." << endl;
			helpMessage();
			return 1;
		}
	} else {
		cout << "Error: Invalid number of arguments." << endl;
		helpMessage();
		return 1;
	}

	return 0;
} // main

// End of main.cpp
