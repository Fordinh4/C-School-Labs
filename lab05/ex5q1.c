/* Purpose: Valid Sudoku
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://www.youtube.com/watch?v=TjFXEUCMqI8 
 */

#include <stdio.h>

int main() {
    int n = 9, m = 9;
    int a[n][m];

    // Input the sudoku board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%1d", &a[i][j]); // Read a single digit as an integer
        }
    }

    // Check if valid or not
    int k, row[9][9] = {0}, col[9][9] = {0}, grid[9][9] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Because the index of the array run from 0 to 8
            int num = a[i][j] - 1;  

            // To determine the index of the 3x3 grid
            // Treat the 3x3 grid as an array run from 0 to 8
            k = i/3 * 3 + j/3;

            if(row[i][num] || col[j][num] || grid[k][num]){
                // To check the duplicate
                // i = 0, num = 3, and row[i][num] means that is number (3+1) 4 in the first row or not (is 4 in row[0][3] = 0 or 1 (false or true))  

                printf("Invalid\n");
                return 0;
            }

            // Mark that row ,col and grid has that number
            row[i][num] = col[j][num] = grid[k][num] = 1;
        }
        
    }
    printf("Valid\n");

}
