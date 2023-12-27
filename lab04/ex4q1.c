/* Purpose: Expression interpreter
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */

#include<stdio.h>
// net profit = total revenue - total expense

int main(){
    float totalRevenue = 0.0, TotalExpense = 0.0, netProfit = 0.0, temp = 4;

    char crops[] = {'C', 'T', 'P', 'L'};
    float salePrice[] = {0.50, 1.25, 3.00, 1.00};
    float purchasePrice[]= {0.05, 0.25, 0.70, 0.30};
    char c1, c2;

    while (1) // Infinite loop
    {
        // When reading characters, getchar provides more predictable behavior regarding buffered input. With scanf, lingering characters like newline (\n) can remain in the buffer, leading to unexpected behavior in subsequent reads.
        c1 = getchar();
        if (c1 == EOF || c1 == '\n') break;  // Check for end-of-file or newline

        c2 = getchar();
        if (c2 == EOF || c2 == '\n') break;  // Check for end-of-file or newline
                
        for (int i = 0; i < 4; i++)
        {
            if (c2 == crops[i])
            {
                if (c1 == '/')
                {
                    totalRevenue += salePrice[i];
                }

                TotalExpense += purchasePrice[i];
            }
        }
        
    }
    
    netProfit = totalRevenue - TotalExpense;

    if (netProfit < 0) {
        printf("Net profit: -$%.2f\n", -netProfit); 
    } else {
        printf("Net profit: $%.2f\n", netProfit);
    }

}