# Huffman-Compressor

**Author:** Nicolas Micuda  
**Project Type:** Individual  

## Description  
This project implements a compressor and decompressor based on the Huffman algorithm.  
It compresses text files by reducing their size according to character frequencies and decompresses them to retrieve the original file.  

## Instructions  

### Compilation  
```bash
gcc -o huffman main.c file_io.c huffman_tree.c
```

### Execution  

#### Compression  
```bash
./huffman -c <input_file> <compressed_file>
```
Example:  
```bash
./huffman -c test.txt output.bin
```

#### Decompression  
```bash
./huffman -d <compressed_file> <output_file>
```
Example:  
```bash
./huffman -d output.bin decompressed.txt
```

## Features  

### Compression  
- Calculates character frequencies.  
- Constructs a Huffman tree.  
- Generates optimal binary codes.  
- Serializes the tree and compressed data into a binary file.  

### Decompression  
- Reads the Huffman tree from the compressed file.  
- Decodes the compressed bits to reconstruct the original file.  

## Improvements Needed  
There is a minor issue where the last characters are sometimes not correctly printed in the output file.  

### Future Enhancements  
- Implement a feature to analyze the algorithm's efficiency by comparing the compressed file size with the original.  
- Extend support to other file types, such as audio and image files.
