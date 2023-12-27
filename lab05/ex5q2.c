/* Purpose: Solving magic square
 * Author: Quoc Dinh
 * Date: Fall 2023
 * References: https://nikamanish.github.io/ruby/recursive-backtracking-solution-to-magic-square/ 
 */

#include "lab05.h"

// Do not touch anything in this main function (used for testing purposes)
int main(void) {
    return test_magic(magic);
}

// This function is a non-recursive function that checks whether a given grid[n][n] is a magic square.
// Complete the function definition:
int check(int n, int grid[n][n]) {
    int diagonal1Sum = 0, diagonal2Sum = 0, magicSum = (n * (n * n + 1)) / 2;

    for (int i = 0; i < n; i++)
    {
        int rowSum = 0, colSum = 0;

        diagonal1Sum += grid[i][i];
        diagonal2Sum += grid[i][(n-1) - i];

        for (int j = 0; j < n; j++)
        {
            colSum += grid[j][i];
            rowSum += grid[i][j];   
        }

        if (rowSum != magicSum || colSum != magicSum){
            return 0;
        }
    }

    if (diagonal1Sum != magicSum || diagonal2Sum != magicSum) return 0;

    return 1;
}

// This function is a recursive function that intends to solve a given grid[n][n] as in the lab05 description.
// Complete the function definition:
int magic(int n, int grid[n][n]) {
    // Find the first empty cell (with a value of 0)
    // Set the row and col = -1 so that the loop will stops as soon as it finds the first empty cell in the grid
    int row = -1, col = -1;
    for (int i = 0; i < n && row == -1; i++) {
        for (int j = 0; j < n && row == -1; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
            }
        }
    }

    // Base case: If there are no empty cells, check if it's a magic square
    if (row == -1) {
        return check(n, grid);
    }

    // Try different values in the current cell
    for (int num = 1; num <= n * n; num++) {
        // Check if the number is not used in the row or column
        int isUsed = 0;
        for (int i = 0; i < n; i++) {
            if (grid[row][i] == num || grid[i][col] == num) {
                isUsed = 1;
                break;
            }
        }

        if (!isUsed) {
            grid[row][col] = num;

            // Recursively move to the next empty cell
            if (magic(n, grid)) {
                return 1; // Found a solution
            }

            grid[row][col] = 0; // Backtrack and find another number to fill it in
        }
    }

    return 0; // No solution found so escape the current recursion and backtrack it
}
