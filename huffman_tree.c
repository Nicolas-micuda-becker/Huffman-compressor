#include "huffman.h"

HuffmanNode *create_node(char character, int frequency) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

MinHeap *create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (HuffmanNode **)malloc(capacity * sizeof(HuffmanNode *));
    return heap;
}

void swap_nodes(HuffmanNode **a, HuffmanNode **b) {
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->frequency < heap->nodes[smallest]->frequency) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right]->frequency < heap->nodes[smallest]->frequency) {
        smallest = right;
    }
    if (smallest != idx) {
        swap_nodes(&heap->nodes[smallest], &heap->nodes[idx]);
        min_heapify(heap, smallest);
    }
}

void insert_min_heap(MinHeap *heap, HuffmanNode *node) {
    heap->size++;
    int i = heap->size - 1;

    while (i > 0 && node->frequency < heap->nodes[(i - 1) / 2]->frequency) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap->nodes[i] = node;
}

HuffmanNode *extract_min(MinHeap *heap) {
    HuffmanNode *min_node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);
    return min_node;
}

HuffmanNode *build_huffman_tree(int frequencies[]) {
    MinHeap *heap = create_min_heap(ASCII_SIZE);

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequencies[i] > 0) {
            insert_min_heap(heap, create_node((char)i, frequencies[i]));
        }
    }

    while (heap->size > 1) {
        HuffmanNode *left = extract_min(heap);
        HuffmanNode *right = extract_min(heap);

        HuffmanNode *new_node = create_node('\0', left->frequency + right->frequency);
        new_node->left = left;
        new_node->right = right;

        insert_min_heap(heap, new_node);
    }

    HuffmanNode *root = extract_min(heap);
    free(heap->nodes);
    free(heap);
    return root;
}

void generate_huffman_codes(HuffmanNode *root, char *code, int depth, char *codes[]) {
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';  
        codes[(unsigned char)root->character] = strdup(code);  
        return;
    }

    if (root->left != NULL) {
        code[depth] = '0';
        generate_huffman_codes(root->left, code, depth + 1, codes);
    }

    if (root->right != NULL) {
        code[depth] = '1';
        generate_huffman_codes(root->right, code, depth + 1, codes);
    }
}

/*void print_huffman_tree(HuffmanNode *root, int depth) {
    if (!root) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (root->character == '\0') {
        printf("[Nœud interne : %d]\n", root->frequency);
    } else {
        if (root->character == '\n') {
            printf("'\\n' : %d\n", root->frequency);
        } else if (root->character >= 32 && root->character <= 126) {
            printf("'%c' : %d\n", root->character, root->frequency);
        } else {
            printf("'\\x%02x' : %d\n", (unsigned char)root->character, root->frequency);
        }
    }

    print_huffman_tree(root->left, depth + 1);
    print_huffman_tree(root->right, depth + 1);
}*/


HuffmanNode *read_huffman_tree(FILE *input_file) {
    char flag = 0;
    size_t bytes_read = fread(&flag, 1, 1, input_file); 
    if (bytes_read != 1) {
        //printf("Erreur : impossible de lire le flag.\n");
        return NULL;
    }
    //printf("Flag lu : '%c', bytes read: %zu\n", flag, bytes_read);

    if (flag == '1') { 
        char character = 0;
        fread(&character, sizeof(char), 1, input_file);
        //printf("Lecture d'une feuille : '%c'\n", character);
        return create_node(character, 0); 
    } else if (flag == '0') { 
        //printf("Lecture d'un nœud interne\n");
        HuffmanNode *left = read_huffman_tree(input_file);
        HuffmanNode *right = read_huffman_tree(input_file);
        HuffmanNode *node = create_node('\0', 0);
        node->left = left;
        node->right = right;
        return node;
    } else { 
        //printf("Flag invalide '%c' trouvé dans le fichier.\n", flag);
        return NULL;
    }
}




void write_huffman_tree(FILE *output_file, HuffmanNode *node) {
    if (!node) return;

    if (node->left == NULL && node->right == NULL) { 
        char flag = '1';
        fwrite(&flag, 1, 1, output_file); 
        fwrite(&node->character, sizeof(char), 1, output_file); 
        //printf("Écriture d'une feuille : '%c'\n", node->character);
    } else { 
        char flag = '0';
        fwrite(&flag, 1, 1, output_file); 
        //printf("Écriture d'un nœud interne\n");
        write_huffman_tree(output_file, node->left); 
        write_huffman_tree(output_file, node->right); 
    }
}
