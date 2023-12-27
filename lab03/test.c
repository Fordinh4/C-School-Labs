#include<stdlib.h>
#include<stdio.h>

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}




int main(){
    int a = 10, b = 5;

    // printf("Before: %d, %d\n", a, b);
    // swap(&a,&b);

    // printf("\nAfter: %d, %d", a, b);


    int array1[2][3] = {{5,4,3}, {2,1,0}};
    char str[] = "This is a cool trick!";

    // printf("%d", *(*(array1 + 0) + 2));
    // printf("%d\n", *(array1));
    // printf("%c", *(str+1));

    // int array[2][3] = {{5,4,3}, {2,1,0}};
    // int *p;
    // // pointer to the first element of the array
    // // p = *array; // print the address of value 5
    // // p = *array+1; // print the address of value 4
    // p = *(array+1); // print the address of value 2

    // printf("%d", *p); // deference it and print the given value based on the address

    int a1D[10] = {1, 5, 6, 3, 2, 89, 34, 3, 9, 10};
    int *q;
    // q = a1D + 10 -1;
    // *q = 11; // reinitialized the last element of the array | a[10-1] = 11

    // q = a1D; // point to the address of the first element of the array
    q = a1D+1; // point to the address of the second element of the array

    printf("%d\n", a1D);


    


}