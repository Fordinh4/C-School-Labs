/* Purpose: Dynamic Storage Allocation #2
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */
#include "ex8q1.h"

// Function to find the insertion position for a new index
// If the index already exists in the array, "found" will set to 1
int findInsertPosition(float *indices, float index, int currentSize, int *found){
    for (int i = 0; i < currentSize; i++)
    {
        if (indices[i] == index)
        {
            *found = 1;
            return i; // Return the position of exiting index
        }
        if (indices[i] > index && index > indices[i-1])
        {
            return i; // Return the position right before the first index that's larger than the index we're trying to insert
        }
    }
    return currentSize; // The index should be inserted at the end

}


// Function to print the array
void printArray(int *values, int currentSize){
    printf("[");

    for (int i = 0; i < currentSize; i++)
    {
        printf("%d", values[i]); // values[i] is the same as *(values + i)
        if (i < currentSize - 1) printf(", ");
    }

    printf("]\n");
}


int main(void) {
    int is_print, value, currentSize = 0, maxCapacity = 10;
    float index;

    // Allocate initial parallel arrays
    float *indices = (float*) malloc(maxCapacity * sizeof(float));
    int *values = (int*) malloc(maxCapacity * sizeof(int));

    while (!feof(stdin)) {
        // Use the read_line function from ex7q1.h here! Do not try to parse the
        // input yourself (that's a lot harder)
        read_line(&is_print, &index, &value);
        
        if (is_print)
        {
            printArray(values, currentSize);

        } else{
            // add the element in the right order and update the parallel arrays
            int found = 0;
            int position = findInsertPosition(indices, index, currentSize, &found);

            if (found)
            {
                values[position] = value;

            } else {

                // Check if we need to expand the arrays
                if (currentSize >= maxCapacity){
                    maxCapacity *= 2;
                    indices = (float*) realloc(indices, maxCapacity * sizeof(float));
                    values = (int*) realloc(values, maxCapacity * sizeof(int));
                }

                // Shift up larger indices to make space for the new index
                for (int i = currentSize; i > position; --i)
                {
                    indices[i] = indices[i-1];
                    values[i] = values[i-1];
                }

                // Insert the new element in both parallel arrays
                indices[position] = index;
                values[position] = value;
                currentSize ++;
                
            }

        }
        
    }

    // Free up the memory
    free(indices);
    free(values);
}
