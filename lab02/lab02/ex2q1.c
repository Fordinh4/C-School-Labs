#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {// This program finds the maximum element in an array
	int length, index = 0;
	if (scanf("%d", &length) == 1) {
		int array[length];
		for (int i = 0; i < length; i++) {
			if (scanf("%d", &array[i]) != 1)
				exit(100);
			if (array[index] < array[i]) 
				// Segmentation fault here if put index = -INT_MAX
				index = i;
		}
		printf("The maximum element is %d\n", array[index]);
	}
	return 0;
}
