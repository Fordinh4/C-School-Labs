/* Purpose: Dynamic Storage Allocation
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);

    int aislesCount[n], aislesCapacity[n];
    for (int i = 0; i < n; i++) {
        // To keep track of how many products have been add (treat like i in for loop)
        aislesCount[i] = 0; 

        // To keep track of the current allocated capacity for the array which start with a size of 1
        aislesCapacity[i] = 1; 
    }

    // Initialize the size n aisles which will contain the IKEA products later (bigArray)
    char **aisles = (char **) malloc(n * sizeof(char *));

    // Set up the allocated memory for the inner array (arrays inside the big array | innerArrays)
    for (int i = 0; i < n; i++) {
        aisles[i] = (char*) malloc(aislesCapacity[i] * sizeof(char));
    }

   while (1) {
        int serialCode, temp_aisle;
        char productName;

        // Read the serialCode
        if (scanf("%d", &serialCode) != 1) {
            int check = getchar();

            if (check == EOF || check == '\n') break;
        }

        // Check if it's a print command
        if (serialCode == 0) {

            scanf("%d", &temp_aisle);  // Read the aisle index
            for (int i = 0; i < aislesCount[temp_aisle]; i++) {
                printf("%c", aisles[temp_aisle][i]);
            }
            printf("\n");

        } else {
            getchar();  // Consume the "\n"
            scanf("%c", &productName);
            
            // Calculate which aisle will it be
            temp_aisle = serialCode % n;

            // Increase the size of the chosen aisle
            aislesCapacity[temp_aisle]++;

            // Reallocating memory to make sure there's enough space in the chosen aisle (make it bigger)
            aisles[temp_aisle] = (char *) realloc(aisles[temp_aisle], (aislesCapacity[temp_aisle]) * sizeof(char));

            // Add new product into the available spot (like 1 -> ['G', '_', ...], or bigArray[i][j])
            aisles[temp_aisle][aislesCount[temp_aisle]] = productName;

            // Increase the count by 1 for the chosen aisle (like i++)
            aislesCount[temp_aisle]++;
        }
    }

    // Free up the memory space
    for (int i = 0; i < n; i++) {
        free(aisles[i]);
    }
    free(aisles);

    return 0;
}
