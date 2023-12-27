/* Purpose: To compute x * max + y * min for a user-provided set of integers, where x * max + y * min are additional user-input integers following the set.
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */

#include<stdio.h>

int main(){
    int N = 22, arrayN[N], max = -1e8, min = 1e8;

    printf("Enter 22 integers: ");
    for (int i = 0; i < N; i++)
    {
        if (scanf("%d", &arrayN[i]) != 1) return 100;
    }

    int x = arrayN[N-2], y = arrayN[N-1];

    for (int i = 0; i < N - 2; i++)
    {
        if (arrayN[i] > max) max = arrayN[i];
        else if (arrayN[i] < min) min = arrayN[i];
    }

    printf("x * max + y * min: %d\n", x * max + y * min);
    
}