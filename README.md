# Huffman Compression
This program uses Huffman algorithm to compress / decompress files.



## Environment and Build

### Windows

Tested on **Visual Studio 2010**.

### Linux

Tested on **Ubuntu 16.04 LTS** using **g++ 7.4.0**.

- Run `make` to compile.

You will find the executable file called `huff` in the same directory.



## Usage

`./huff --option [source] [destination]` 

Examples: 

- Run `./huff -c [source file name] [output file name]` to compress a file.

- Run `./huff -d [compressed file name] [output file name]` to decompress a file.

- Run `./huff -h` to see help information.