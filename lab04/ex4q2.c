/* Purpose: Sorting and searching
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */

#include<stdio.h>

void bubbleSort(float a[], int n){
    // To sort the array in ascending order

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (a[j] < a[i])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void cumulativeSum(float temp[], float array[], int n){
    // Like fibonacci - sum of the previous number
    temp[0] = array[0];

    for (int i = 1; i < n; i++)
    {
        temp[i] = temp[i-1] + array[i];
    }
    
}

int binarySearch(float a[], int n, float x) {
    // If x is less than the first element or greater than the last element, we return the first of last element, respectively.
    if (x <= a[0]) {
        return 0;
    }
    if (x >= a[n-1]) {
        return n-1;
    }

    // Binary search
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = (start + end) / 2;

        if (a[mid] == x) {
            return mid;
        }

        if (a[mid] < x) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    // If the value at 'start' is greater than x, return 'start - 1' as the rounded down index
    if (start < n && a[start] > x) {
        return start - 1;
    }
    
    return start;

}

int main(){
    int n;
    scanf("%d", &n);

    float array[n], sumArray[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &array[i]);
    }

    bubbleSort(array, n);
    cumulativeSum(sumArray, array, n);

    while (1)
    {
        float truckLimit;

        if ((scanf("%f", &truckLimit)) != 1) {
            // Clear any invalid characters until a newline or EOF

            int check = getchar();
            if (check == EOF || check == '\n') break;
        }

        int numberOfBox = binarySearch(sumArray, n, truckLimit) + 1;
        printf("%d\n", numberOfBox);
    }
    
}