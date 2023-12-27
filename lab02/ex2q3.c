/* Purpose: To apply discount for online bookstore
 * Author: Quoc Dinh
 * Date: 9/17/2023
 * Persons discussed w/: None
 * References: None
 */

#include<stdio.h>
#include<stdlib.h>

int validateInput(){
    // This function is to validate and return the input
    int temp;
    if (scanf("%d", &temp) != 1 || 0 > temp || temp > 100000) exit(100);

    return temp;
}

int main(){
    int hardCovers, softCovers, ebooks;
    float orderTotal;
    int hardCovers_price = 15, softCovers_price = 12, ebooks_price = 7;

    // Taking the input
    printf("How many hardcover books are you buying? ");
    hardCovers = validateInput();

    printf("How many softcover books are you buying? ");
    softCovers = validateInput();

    printf("How many ebooks are you buying? ");
    ebooks = validateInput();

    // Calculate the total price before the promotional discounts
    orderTotal = hardCovers*hardCovers_price + softCovers*softCovers_price + ebooks*ebooks_price;

    // Applying the coupons
    if (hardCovers >= 2) orderTotal -= 5;
    if (softCovers >= 4) orderTotal -= 10;
    if ((softCovers + hardCovers) >= 6) orderTotal -= 20;

    // Applying the percentage discounts
    float percentage_discount = 1.0;
    if (hardCovers >= 1 && softCovers >= 1 && ebooks >= 1) percentage_discount -= 0.03;
    if (ebooks >= 3) percentage_discount -= 0.04;
    if (orderTotal > 75) percentage_discount -= 0.1;
    if (orderTotal > 150) percentage_discount -= 0.15;

    // Calculating the final total
    orderTotal *= percentage_discount;

    // Printing out the total
    printf("Order total: $%.2f\n", orderTotal);
}