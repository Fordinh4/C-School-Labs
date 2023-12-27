/* Purpose: Implement a simplified version of the dice game Zanzibar
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://www.shiksha.com/online-courses/articles/rand-and-srand-functions-in-c-programming/
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void bubbleSort(int a[], int n){
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


int calculatePoint(int a[], int n) {
    // To calculate the total points

    int points = 1;

    int products[] = {4*5*6, 1*1*1, 2*2*2, 3*3*3, 4*4*4, 5*5*5, 6*6*6, 1*2*3};
    int scores[] = {1000, 999, 998, 997, 996, 995, 994, 993};

    for (int i = 0; i < n; i++) {
        points *= a[i];
    }

    for (int i = 0; i < 8; i++) {
        
        if (points == products[i]) {
            // Check for edge cases like: [1,1,6] or [1,2,4]
            if (points == 1*2*3 && a[2] != 3) continue;
            if (points == 2*2*2 && a[2] != 2) continue;
            return scores[i];
        }
    }

    // If the roll isn't listed above the points are calculated as follows:
    return 100*a[2] + 10*a[1] + a[0];
}


int rolledResult(int dices){
    // To display the ascending, randomize numbers and to calculate the points

    int array[dices];

    for (int i = 0; i < dices; i++)
    {
        // Using modulo (%6) to limit the range from 0 to 5 and adding 1 to increase the range from 1 to 6.
        array[i] = (rand()%6) + 1;
    }

    // Sort the array
    bubbleSort(array, dices);

    printf("You rolled: ");
    for (int i = 0; i < dices; i++)
    {
        printf("%d ", array[i]);
    }

    int caclPoint =  calculatePoint(array, dices);
    printf("= %d points\n",caclPoint);

    return caclPoint;
}


int playerTurn(int currentPlayer, int turn, int dices){
    // To display the current player turn and result

    int result;
    char choice;

    printf("Turn %d player %d: ", turn, currentPlayer);
    scanf("%c", &choice);
    getchar(); // To remove the left over newline character (\n) in the input buffer after pressing Enter.

    if (choice == 'r'){
        result = rolledResult(dices);
        return result;
    }
    // } else if (choice == 's') 
    return 0;
}


void roundReport(int player1Result, int player1Lives, int player2Result, int player2Lives){
    // To display the result after each rounds

    if (player1Result > player2Result){
        printf("Player 1 wins this round with %d points\n", player1Result);

    } else if (player1Result < player2Result){
        printf("Player 2 wins this round with %d points\n", player2Result);

    } else {
        printf("Both players tied this round with %d points\n", player2Result);
    }

    printf("Player 1 lives = %d\nPlayer 2 lives = %d\n\n", player1Lives, player2Lives);
}


int main(){
    // To run the mechanic of the game

    int player1Lives = 3, player2Lives = 3, turns = 3, dices = 3, currentPlayer = 1;
    int result = 0;
    int player1Result = 0, player2Result = 0;
    srand(time(NULL));
    // The "seed" is like the initial shuffle of the face of the dice and since the time always changing, the seed also change. This will make sure we have different sequence of random numbers.
    // time(NULL) is to get the current time which represents the number of seconds since epoch.

    while (player1Lives > 0 && player2Lives > 0){
        for (int turn = 0; turn < turns; turn++)
        {
            result = playerTurn(currentPlayer, turn + 1, dices);
            if (result == 0) break;
            else {
                if (currentPlayer == 1) player1Result = result;
                else if (currentPlayer == 2) player2Result = result; 
            } 
        }

        if (currentPlayer == 2){
            if (player1Result > player2Result) player2Lives --;
            else if (player1Result < player2Result) player1Lives --;
            
            roundReport(player1Result, player1Lives, player2Result, player2Lives);
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // If true then switch to 2 else 1.
    } 
    
    // Display the final result
    if (player1Lives > player2Lives) printf("Player 1 wins!\n");
    else printf("Player 2 wins!\n");
}
