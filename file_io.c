#include "huffman.h"


void count_character_frequencies(const char *filename, int frequencies[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    memset(frequencies, 0, sizeof(int) * ASCII_SIZE);

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        frequencies[ch]++;
    }

    fclose(file);
}



static unsigned char bit_buffer = 0;
static int bit_count = 0;

void write_bits(FILE *output, const char *code) {

    for (size_t i = 0; code[i] != '\0'; i++) {
        bit_buffer = (bit_buffer << 1) | (code[i] - '0');
        bit_count++;

        if (bit_count == 8) {
            fputc(bit_buffer, output);
            bit_buffer = 0;
            bit_count = 0;
        }
    }
}

void flush_bits(FILE *output) {
    if (bit_count > 0) {
        bit_buffer <<= (8 - bit_count); 
        fputc(bit_buffer, output);
    }
}

void compress_file(const char *input_filename, const char *output_filename, HuffmanNode *root, char *codes[]) {
    FILE *input = fopen(input_filename, "r");
    if (!input) {
        perror("Erreur d'ouverture du fichier d'entrée");
        return;
    }

    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        perror("Erreur d'ouverture du fichier de sortie");
        fclose(input);
        return;
    }

    printf("Écriture de l'arbre de Huffman dans le fichier...\n");
    write_huffman_tree(output, root);

    printf("Compression des données...\n");
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        char *code = codes[(unsigned char)ch];
        write_bits(output, code);  
    }
    flush_bits(output);

    fclose(input);
    fclose(output);
}




void decompress_file(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "rb");
    if (!input) {
        perror("Erreur d'ouverture du fichier d'entrée");
        return;
    }

    FILE *output = fopen(output_filename, "w");
    if (!output) {
        perror("Erreur d'ouverture du fichier de sortie");
        fclose(input);
        return;
    }

    printf("Lecture de l'arbre de Huffman depuis le fichier...\n");
    HuffmanNode *root = read_huffman_tree(input);

    if (!root) {
        printf("Erreur lors de la lecture de l'arbre de Huffman\n");
        fclose(input);
        fclose(output);
        return;
    }

    printf("Arbre de Huffman lu avec succès.\n");

    HuffmanNode *current = root;
    int bit_buffer = 0;
    while ((bit_buffer = fgetc(input)) != EOF) {
        for (int i = 7; i >= 0; i--) {  
            int bit = (bit_buffer >> i) & 1;
            current = (bit == 0) ? current->left : current->right;

            if (current->left == NULL && current->right == NULL) {
                fputc(current->character, output);
                current = root;  
            }
        }
    }
    fclose(input);
    fclose(output);
}

