/* Purpose: Spelling Checker
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://en.wikipedia.org/wiki/Levenshtein_distance#Definition, https://www.youtube.com/watch?v=Dd_NgYVOdLk, https://www.youtube.com/watch?v=nrO_pXGZc3Y
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To determine the minimum of 3 value.
#define MIN3(a, b, c) (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c)

int levenshtein_distance(const char *s1, const char *s2)
{
    int len1 = strlen(s1), len2 = strlen(s2);

    // +1 in both dimensions is to accommodate for the empty string (prefix) comparison.
    int matrix[len1 + 1][len2 + 1];

    // Initialize the first column and row of the matrix.
    for (int x = 0; x <= len1; x++)
        matrix[x][0] = x;
    for (int y = 0; y <= len2; y++)
        matrix[0][y] = y;

    // Iterate over the matrix, filling in each cell starting with matrix[1][1] since we are already initialized the first row and column.
    for (int x = 1; x <= len1; x++)
    {
        for (int y = 1; y <= len2; y++)
        {
            // Check if the current characters in each string are the same.
            // If they are, the cost of substitution is 0; otherwise, it's 1.
            int cost = (s1[x - 1] == s2[y - 1]) ? 0 : 1;

            // - matrix[x-1][y] + 1: cost of a deletion (one edit from above cell plus one deletion).
            // - matrix[x][y-1] + 1: cost of an insertion (one edit from left cell plus one insertion).
            // - matrix[x-1][y-1] + cost: cost of a substitution (diagonal cell cost plus substitution cost if any).
            matrix[x][y] = MIN3(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1, matrix[x - 1][y - 1] + cost);
        }
    }

    // The bottom right cell contain the Levenshtein distance between words.
    return matrix[len1][len2];
}


int find_closest_word(char *word, char **dictionary, int n)
{
    int min_distance = 1e9;
    int distance, index_of_closest_word = -1;

    // Compare each word in the sentence with the dictionary.
    for (int i = 0; i < n; i++)
    {
        distance = levenshtein_distance(word, dictionary[i]);
        if (distance < min_distance)
        {
            min_distance = distance;
            index_of_closest_word = i;
        }
    }

    return index_of_closest_word;
}


int main()
{
    int n, m;
    scanf("%d %d\n", &n, &m); // Read the number of dictionary words and sentences.

    // Allocate memory for the dictionary (big array of pointers).
    char **dictionary = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; ++i)
    {
        // dictionary words = pointer in that big array named dictionary .
        dictionary[i] = (char *)malloc(101 * sizeof(char)); // Maximum word length is 100
        scanf("%s", dictionary[i]);                         // Read each dictionary word
    }

    // Consume the end of line after reading dictionary words.
    getchar();

    // Process each sentence m times.
    for (int i = 0; i < m; i++)
    {
        char sentence[2001];          // Maximum sentence length of 2000 characters
        fgets(sentence, 2001, stdin); // Read the sentence including space and newline

        // Tokenize the sentence by space and "\n" 
        // strtok work by replacing the delimiter with the NULL terminator ("\0") in sentence | Modify the original string and like a static variable.
        char *word = strtok(sentence, " \n");

        // We might need to keep track of whether it's the first word in the sentence to format output correctly.
        int first_word = 1;
        while (word != NULL)
        {
            int word_found = 0;
            for (int j = 0; j < n; ++j)
            {
                // Compare between the dictionary words and the word that need to check.
                if (strcmp(word, dictionary[j]) == 0)
                {
                    word_found = 1;
                    break;
                }
            }

            // Find the closet distance between dict words and the current word.
            if (!word_found)
            {
                int closest_word_index = find_closest_word(word, dictionary, n);
                word = dictionary[closest_word_index]; // word point to the memory location where that string is.
            }


            // Print the word, with a space if it's not the first word.
            if (!first_word) printf(" ");
            first_word = 0;
            printf("%s", word);

            // Get the next word.
            // It points to the next word in the original string, and strtok keeps track of where to start looking for the next token. When there are no more tokens, strtok returns NULL, and the loop will end.
            word = strtok(NULL, " \n");
        }
        printf("\n"); // Print new line at the end of the sentence
    }

    // Free the allocated memory.
    for (int i = 0; i < n; ++i)
    {
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}
