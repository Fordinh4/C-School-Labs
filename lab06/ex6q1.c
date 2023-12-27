/* Purpose: Program organization, recursive calls
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: none
 */

#include "ex6q1.h"

#define LEN 200000000
uint32_t MEMO[LEN];

// This function should be pure recursion - no dynamic programming allowed
uint32_t exp_mod_1(uint32_t base, uint32_t exp, uint32_t modulo) {

    EXP_MOD_1_CALL_COUNT += 1;

    // Base case
    if (exp == 0) return 1;

    // If exponent is odd
    if (exp % 2 == 1) {
        // Instead of b^7, it's b * b^(7-1)
        return (base * exp_mod_1(base, exp - 1, modulo)) % modulo;
    } 

    // If exponent is even, divide exponent by half
    return (exp_mod_1(base, exp/2, modulo) * exp_mod_1(base, exp/2, modulo)) % modulo;
    

}

// This function should store the values of previous calls to exp_mod_2 in an
// array and use them for later calculations.
uint32_t exp_mod_2(uint32_t base, uint32_t exp, uint32_t modulo) {

    EXP_MOD_2_CALL_COUNT += 1;

    // Base case
    if (exp == 0) return 1;

    // Check if the computation have been done before
    if (MEMO[exp] != 0) return MEMO[exp];

    // If exponent is odd
    if (exp % 2 == 1)
    {
        // Instead of b^7, it's b * b^(7-1)
        // Save the calculation for next time
        MEMO[exp] = (base * exp_mod_2(base, exp - 1, modulo)) % modulo;
        return MEMO[exp];
    }

    // If exponent is even, divide exponent by half
    uint32_t temp = exp_mod_2(base, exp/2, modulo);
    MEMO[exp] = (temp * temp) % modulo;

    return MEMO[exp]; 

}

int main(void) {
    uint32_t base, exp, modulo;

    if (scanf("%d %d %d", &base, &exp, &modulo) != 3) {
        return 1;
    }

    uint32_t mod_1 = exp_mod_1(base, exp, modulo);
    uint32_t mod_2 = exp_mod_2(base, exp, modulo);

    fprintf(stdout, "exp_mod_1 calls: %d\n", EXP_MOD_1_CALL_COUNT);
    fprintf(stdout, "exp_mod_2 calls: %d\n", EXP_MOD_2_CALL_COUNT);
    fprintf(stdout, "%d == %d\n", mod_1, mod_2);
	return 0;
}
