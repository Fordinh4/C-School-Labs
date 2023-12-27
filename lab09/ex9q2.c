/* Purpose: String arithmetic
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
 */

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
    char *result = (char *)malloc(max_len + 2); // +1 for possible carry and +1 for null terminator

    int carry = 0;
    int index = 0;
    int i, j, sum;

    // Outer loop - iterate over the longest length + 1 for potential carry.
    for (i = len1 - 1, j = len2 - 1; i >= -1 || j >= -1; --i, --j, ++index) { // since i ran to -1 that's why i need to --index at the end and i should do double for loops which are easier to look at

        sum = carry; // Initialize sum with the current carry.

        // Inner loop - executed at most once to add digits from num1 and num2.
        for (int k = 0; k < 1; ++k) { // NO NEED FOR THIS LOOP
            if (i >= 0){
                sum += num1[i] - '0';
            }
            if (j >= 0) {
                sum += num2[j] - '0';
            }
            
            carry = sum / 10; // Update carry for the next iteration.
        }
        
        result[index] = (sum % 10) + '0'; // Store the last digit of sum.
    }

    // If there's a remaining carry, add it to the result.
    if (index > 0 && result[index - 1] == '0') {
        index--; // Do not increase the length if the last digit is a '0' carry.
    }

    result[index] = '\0'; // Null-terminate the result string.

    // The result is currently reversed, so reverse it before returning.
    reverse(result);
    
    return result;
}



// Function to concatenate two integers represented as strings
char *concat(const char* num1, const char* num2) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    char* result = malloc(length1 + length2 + 1);

    // Copy two different strings into one
    strcpy(result, num1);
    strcat(result, num2);

    return result;
}

// Function to rotate a integer represented as a string
char *rot(const char* num, int rot) {
    // Example we have this input:
    // 12345 rot 7 and the expected output will be 34512
    // After taking the mod for rot which is 2, we need to move 12 to the back

    // Take the number from rot to length to put in the beginning of the string
    // So we deal with 345 first and put in the beginning of the result string
    // By using count independently, I make sure the 345 will be at the start of the string

    int length = strlen(num);
    rot %= length; // In case of rot > length of the number
    char* result = (char*)malloc(length + 1);

    int count = 0;

    // Take the number from rot to length to put in the beginning of the string
    for (int i = rot; i < length; i++) {
        result[count++] = num[i];
    }

    // This will append the first 'rot' characters to the end of result
    for (int i = 0; i < rot; i++) {
        result[count++] = num[i];
    }

    // Null-terminate the result string so it make an array of char into a string
    result[count] = '\0';

    // Remove leading zeros if any
    int lead_zero_index = 0;
    while (result[lead_zero_index] == '0' && lead_zero_index < length - 1) { // keep at least one digit
        lead_zero_index++;
    }

    if (lead_zero_index > 0) {
        // Shift the non-zero part of the array to the beginning
        for (int i = 0; lead_zero_index + i < length; i++) {
            result[i] = result[lead_zero_index + i];
        }
        result[length - lead_zero_index] = '\0'; // New null-termination after shifting
    }

    return result;
}


int main() {
    int n;
    scanf("%d\n", &n); // Read the number of operations and consume the newline after it.

    char *num1 = (char *)malloc(101 * sizeof(char)); // Up to 100 digits + null terminator
    char *num2 = (char *)malloc(101 * sizeof(char));
    char op;
    int rot_value;

    // Starting buffer size for the input line.
    char *line = (char *)malloc(256 * sizeof(char)); // Dynamically allocate the line buffer

    for (int i = 0; i < n; i++) {
        // Store the whole line.
        fgets(line, 256, stdin);

        // Read the given line.
        sscanf(line, "%s %c", num1, &op);

        // Allocate memory for the result.
        char *result = NULL;

        // Handle the operation.
        // %*[] means that it read it but it do not store it
        if (op == '+') {
            sscanf(line, "%*s %*c %s", num2); // Store the second operand
            result = add(num1, num2);

        } else if (op == '@') {
            sscanf(line, "%*s %*c %s", num2); // Store the second operand
            result = concat(num1, num2);

        } else if (op == 'r') {
            sscanf(line, "%*s %*s %d", &rot_value); // Store the rotation value
            result = rot(num1, rot_value);
        } 

        // Output the result.
        if (result) {
            printf("%s\n", result);
            free(result); // Free allocated memory for each result
        }
    }

    // Free allocated memory.
    free(num1);
    free(num2);
    free(line);

    return 0;
}