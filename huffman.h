#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

typedef struct MinHeap {
    int size;
    int capacity;
    HuffmanNode **nodes;
} MinHeap;

void count_character_frequencies(const char *filename, int frequencies[]);
void write_bits(FILE *output, const char *code);
void flush_bits(FILE *output);
void generate_huffman_codes(HuffmanNode *root, char *code, int depth, char *codes[]);
//void print_huffman_tree(HuffmanNode *root, int depth);
void compress_file(const char *input_filename, const char *output_filename, HuffmanNode *root, char *codes[]);
void decompress_file(const char *input_filename, const char *output_filename);
HuffmanNode *create_node(char character, int frequency);
MinHeap *create_min_heap(int capacity);
void insert_min_heap(MinHeap *heap, HuffmanNode *node);
HuffmanNode *extract_min(MinHeap *heap);
HuffmanNode *build_huffman_tree(int frequencies[]);
HuffmanNode *read_huffman_tree(FILE *input_file);
void write_huffman_tree(FILE *output_file, HuffmanNode *root);



#endif
