/* Purpose: Sorting
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://en.m.wikipedia.org/wiki/Stooge_sort
 */
#include "ex6q2.h"

// Please don't change anything in this main function!
int main(void) {
    if (!test_bubble(bubble_sort))
        fprintf(stderr, "Bubble sorting failed\n");
    if (!test_gnome(gnome_sort))
        fprintf(stderr, "Gnome sorting failed\n");
    if (!test_insertion(insertion_sort))
        fprintf(stderr, "Insertion sorting failed\n");
    if (!test_custom(custom_sort)) {
        fprintf(stderr, "Custom sorting failed\n");
	}
	return 0;
}

void bubble_sort(int n, int arr[n]) {
    // Continuously swaps adjacent elements if they're in the wrong order until the entire list is sorted.
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

}

// Not very well known, but very easy!
// Check out the description on here https://en.wikipedia.org/wiki/Gnome_sort
void gnome_sort(int n, int arr[n]) {
    // Iteratively scans the list, swapping elements to move them to their correct positions, similar to a garden gnome sorting his flower pots.
    int index = 0;

    while (index < n) {
        if (index == 0) {
            index++;
        }
        if (arr[index] >= arr[index - 1]) {
            index++;
        } else {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

void insertion_sort(int n, int arr[n]) {
    // Builds a sorted list by repeatedly taking one element from the input and inserting it into its correct position within the already sorted part of the list.

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}


void stoogeSort(int arr[], int l, int h) {
    if (l >= h) return;

    // If first element is smaller than last, swap them
    if (arr[l] > arr[h]) {
        int temp = arr[l];
        arr[l] = arr[h];
        arr[h] = temp;
    }

    // If there are more than 2 elements in the array
    if (h - l + 1 > 2) {
        int t = (h - l + 1) / 3;
        
        // Recursively sort the first two-thirds
        stoogeSort(arr, l, h - t);
        
        // Recursively sort the last two-thirds
        stoogeSort(arr, l + t, h);
        
        // Recursively sort the first two-thirds again
        stoogeSort(arr, l, h - t);
    }
}


// The sort you found! (See lab description for details)
void custom_sort(int n, int arr[n]) {
    // Recursively sort the first two-thirds, then the last two-thirds, and then the first two-thirds again, with occasional swaps of the first and last elements.

    stoogeSort(arr, 0, n - 1);
}
