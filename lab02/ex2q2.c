/* Purpose: To convert CAD currency to USD
 * Author: Quoc Dinh
 * Date: 9/17/2023
 * Persons discussed w/: None
 * References: None
 */

#include<stdio.h>
#include<stdlib.h>

int main(){
    int CAD, USD;
    float conversion_rate = 0.75;
    printf("Enter CAD amount: ");

    // Check whether the input is valid or not
    if (scanf("%d", &CAD) != 1 || 0 > CAD || CAD > 100000) exit(100);

    // Convert from CAD to USD and round up if possible
    USD = (CAD * conversion_rate) + 0.5; 
    
    printf("Converted USD amount: $%d\n", USD);

    // Determine the USD bills
    int hundreds = USD / 100, hundreds_remainder = USD % 100;
    int fifties = hundreds_remainder / 50, fifties_remainder = hundreds_remainder % 50;
    int twenties = fifties_remainder / 20, twenties_remainder = fifties_remainder % 20;
    int tens = twenties_remainder / 10, tens_remainder = twenties_remainder % 10;
    int fives = tens_remainder / 5, fives_remainder = tens_remainder % 5;
    int twos = fives_remainder / 2, ones = fives_remainder % 2;
    
    printf("$100 bills: %d\n $50 bills: %d\n $20 bills: %d\n $10 bills: %d\n  $5 bills: %d\n  $2 bills: %d\n  $1 bills: %d\n", hundreds, fifties, twenties, tens, fives, twos, ones);

}   