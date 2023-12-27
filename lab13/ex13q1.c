/* Purpose: Disjoint Sets and Union-Find
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://www.geeksforgeeks.org/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/, https://www.geeksforgeeks.org/sprintf-in-c/, https://www.geeksforgeeks.org/scanf-fscanf-sscanf-scanf_s-fscanf_s-sscanf_s/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tree like structure
typedef struct {
    int *parent;
} DisjointSet;

// Allocate the memory for the array
void initialize(DisjointSet *ds, int size) {
    ds->parent = (int *)malloc(size * sizeof(int));

    // Set each index to point to itself (1 will have root of 1, 2 will be 2 and so on)
    for (int i = 0; i < size; i++) {
        ds->parent[i] = i;
    }
}

// Finding the root of the given element by using recursion
int find(DisjointSet *ds, int element) {
    if (ds->parent[element] != element) {
        ds->parent[element] = find(ds, ds->parent[element]);
    }
    return ds->parent[element];
}

// Join two sets into one by setting one root to other so that it all point to one root
void unionSet(DisjointSet *ds, int element1, int element2) {
    int root1 = find(ds, element1);
    int root2 = find(ds, element2);
    if (root1 != root2) {
        ds->parent[root1] = root2;
    }
}

// Free the memory
void freeDisjointSet(DisjointSet *ds) {
    free(ds->parent);
}


// Define a buffer for FASTIO flag
#ifdef FASTIO
char *buffer;
int buffer_length = 0;
int buffer_capacity;
#endif

// -D name Predefine name as a macro, with definition 1.
// argc should be 4 which include n f k and the program itself
int main(int argc, char *argv[]) {
    if (argc != 4) return 1;

    int n, k;
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &k) != 1) {
        return 1;
    }

    DisjointSet ds; 

    initialize(&ds, k + 1); // +1 for 1-based indexing instead of starting at 0

    #ifdef FASTIO
    buffer_capacity = n*4; // Assuming each line of output takes up to 4 characters (for safety cuz each line only need 'T' or 'F' + '\n' + '\0')
    buffer = (char *)malloc(buffer_capacity * sizeof(char));
    buffer[0] = '\0';
    #endif

    FILE *file = fopen(argv[3], "r");
    if (file == NULL) {
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int x, y;
        char op, result[3];
        sscanf(line, "%c %d %d", &op, &x, &y);


        if (op == 'j') {
            unionSet(&ds, x, y);

        } else if (op == '?') {
            // /0 to complete a string
            result[0] = (find(&ds, x) == find(&ds, y)) ? 'T' : 'F';
            result[1] = '\n';
            result[2] = '\0';

            #ifdef FASTIO
            // Append text to the buffer
            buffer_length += sprintf(buffer + buffer_length, "%s", result); 
            #else
            printf("%s", result);
            #endif
        }
    }

    fclose(file);
    freeDisjointSet(&ds);

    #ifdef FASTIO
    printf("%s", buffer);
    free(buffer);
    #endif

    return 0;
}
