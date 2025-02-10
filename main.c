#include "huffman.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s [-c/-d] <fichier_d'entrée> <fichier_de_sortie>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[2];    
    const char *output_filename = argv[3];   

    if (strcmp(argv[1], "-c") == 0) {
        printf("Début de la compression...\n");

        int frequencies[ASCII_SIZE] = {0};
        count_character_frequencies(input_filename, frequencies);

        
        HuffmanNode *root = build_huffman_tree(frequencies);

        //printf("=== TEST DE L'ARBRE EN MÉMOIRE ===\n");
        //print_huffman_tree(root, 0);

        
        char *codes[ASCII_SIZE] = {0};  
        char code[ASCII_SIZE];  
        code[0] = '\0';  
        generate_huffman_codes(root, code, 0, codes);  

        compress_file(input_filename, output_filename, root, codes);
        printf("Compression terminée avec succès.\n");

    } else if (strcmp(argv[1], "-d") == 0) {
        printf("Début de la décompression...\n");
        
        decompress_file(input_filename, output_filename);
        printf("Décompression terminée avec succès.\n");

    } else {
        fprintf(stderr, "Option invalide. Utilisez -c pour compresser ou -d pour décompresser.\n");
        return 1;
    }

    return 0;
}
