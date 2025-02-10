Project : Huffman-Compressor

Author: Nicolas Micuda

Project-individual: Individual

# Description: 
  This project implements a compressor and decompressor based on the Huffman algorithm.
  The goal is to compress text files by reducing their size according to character frequencies
  and to decompress them to retrieve the original file.

## Instructions:
  -Compilation:
    Command: gcc -o huffman main.c file_io.c huffman_tree.c
  -Execution:
    -> Compression:
        Command: ./huffman -c <input_file> <compressed_file>
        Example: ./huffman -c test.txt output.bin
    -> Decompression:
        Command: ./huffman -d <compressed_file> <output.bin>
        Example: ./huffman -d output.bin decompressed.txt

### Features:
  Compression:
    - Calculates character frequencies.
    - Constructs a Huffman tree.
    - Generates optimal binary codes.
    - Serializes the tree and compressed data into a binary file.
  Decompression:
    - Reads the Huffman tree from the compressed file.
    - Decodes the compressed bits to reconstruct the original file.

#### Point à améliorer:
  There is a minor issue with the last characters, which are sometimes not correctly printed in the output file.

  This project is a basic version of a Huffman compressor that currently works only with text files.
   Future improvements could include:
    - Implementing a feature to analyze the efficiency of the algorithm by comparing the size of the compressed binary file with the original text file.
    - Expanding the compressor to support other file types, such as audio and image files.


