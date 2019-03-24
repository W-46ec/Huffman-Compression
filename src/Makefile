all:	huff

huff:	main.o Compress.o Decompress.o FileHeaderHandler.o FrequencyCounter.o PriorityQueue.o HuffmanTree.o HuffmanTreeNode.o OutBitStream.o InBitStream.o
	g++ -Wall -std=c++11 -o huff main.o Compress.o Decompress.o FileHeaderHandler.o FrequencyCounter.o PriorityQueue.o HuffmanTree.o HuffmanTreeNode.o OutBitStream.o InBitStream.o

main.o:	main.cpp Compress.cpp Decompress.cpp
	g++ -Wall -c main.cpp

Compress.o:	HeaderFormat.h FileHeaderHandler.cpp Compress.cpp InBitStream.h OutBitStream.h HuffmanTree.h FrequencyCounter.h PriorityQueue.h
	g++ -Wall -c Compress.cpp

Decompress.o:	HeaderFormat.h FileHeaderHandler.cpp Decompress.cpp InBitStream.h OutBitStream.h HuffmanTree.h HuffmanTreeNode.h FrequencyCounter.h PriorityQueue.h
	g++ -Wall -c Decompress.cpp

FileHeaderHandler.o:	HeaderFormat.h FileHeaderHandler.cpp
	g++ -Wall -c FileHeaderHandler.cpp

FrequencyCounter.o:	FrequencyCounter.h FrequencyCounter.cpp InBitStream.h HuffmanTreeNode.h PriorityQueue.h
	g++ -Wall -c FrequencyCounter.cpp

PriorityQueue.o:	HuffmanTreeNode.h PriorityQueue.h PriorityQueue.cpp
	g++ -Wall -c PriorityQueue.cpp

HuffmanTree.o:	HuffmanTree.h HuffmanTree.cpp
	g++ -Wall -c HuffmanTree.cpp

HuffmanTreeNode.o:	HuffmanTreeNode.h HuffmanTreeNode.cpp
	g++ -Wall -c HuffmanTreeNode.cpp

InBitStream.o:	InBitStream.h InBitStream.cpp
	g++ -Wall -c InBitStream.cpp

OutBitStream.o:	OutBitStream.h OutBitStream.cpp
	g++ -Wall -c OutBitStream.cpp

clean:
	rm -f huff *.o
