#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a string in place.
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char *add(const char *num1, const char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2 ? len1 : len2);
    
    // Allocate memory for the result.
    char *result = (char *)malloc(max_len + 2); // +2 for possible carry and null terminator.
    if (!result) return NULL;

    int carry = 0;
    int index = 0;
    for (int i1 = len1 - 1, i2 = len2 - 1; i1 >= 0 || i2 >= 0 || carry; i1--, i2--, index++) {
        int digit1 = i1 >= 0 ? num1[i1] - '0' : 0;
        int digit2 = i2 >= 0 ? num2[i2] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result[index] = (sum % 10) + '0';
        carry = sum / 10;
    }
    
    // If there's a remaining carry, add it to the result.
    if (carry) {
        result[index++] = carry + '0';
    }
    result[index] = '\0'; // Null-terminate the result string.

    // The result is currently reversed, so reverse it before returning.
    reverse(result);
    
    return result;
}


// Function to concatenate two big integers represented as strings.
char *concatenate(const char *num1, const char *num2) {
    // Allocate memory for the concatenated result.
    char *result = (char *)malloc(strlen(num1) + strlen(num2) + 1);
    if (!result) return NULL; // Check for successful allocation.
    
    strcpy(result, num1); // Copy the first number into result.
    strcat(result, num2); // Concatenate the second number to result.
    return result;
}

// Function to rotate the digits of a big integer represented as a string.
char *rotate(const char *num, int rotations) {
    int len = strlen(num);
    rotations %= len; // To handle rotations greater than the number length.
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL; // Check for successful allocation.
    
    // Copy the part of the string from the rotation point to the end.
    strncpy(result, num + rotations, len - rotations);
    // Copy the initial part of the string that was rotated to the end.
    strncpy(result + len - rotations, num, rotations);
    result[len] = '\0'; // Null-terminate the result.
    return result;
}

int main() {
    int n, rotations;
    scanf("%d\n", &n); // Read the number of operations

    for (int i = 0; i < n; i++) {
        char num1[101], num2[101], op;
        scanf("%100s %c %100s", num1, &op, num2); // Read the operands and the operator

        char *result;
        switch (op) {
            case '+':
                result = add(num1, num2);
                break;
            case '@':
                result = concatenate(num1, num2);
                break;
            case 'r': // Assuming the input is 'rot', we'll only match 'r'
                // Convert num2 to the number of rotations
                rotations = atoi(num2);
                result = rotate(num1, rotations);
                break;
        }

        printf("%s\n", result);
        free(result); // Don't forget to free the memory allocated for the result
    }

    return 0;
}

