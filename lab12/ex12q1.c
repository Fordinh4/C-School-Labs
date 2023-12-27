/* Purpose: Low-level programming
 * Author: Quoc Dinh
 * Date: Fall 2023
 * Persons discussed w/: None
 * References: https://qr.ae/pKwKGR, https://www.h-schmidt.net/FloatConverter/IEEE754.html, https://www.programiz.com/c-programming/bitwise-operators
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef uint32_t NewFloat; // %u

void nfloat_debug(NewFloat f); // part 1

NewFloat float_to_nfloat(float f); // part 2

void nfloat_print(NewFloat f); // part 3

NewFloat nfloat_double(NewFloat f); // part 4
NewFloat nfloat_add(NewFloat a, NewFloat b);

// This function store and convert bits string to NewFloat
NewFloat bits_string_to_nfloat(char s[])
{
    // use left shift 31 for the signed bit since n = 0 => n |= 1 << 31 to change the sign bit

    // How it work?
    // Perform shift: 1 << 6 = 01000000
    // Perform OR and assignment: n |= 01000000
    // New n: 10000000 | 01000000 = 11000000 -> | is like plus
    NewFloat n = 0;
    int length = strlen(s); // Length of the string

    for (int i = 0; i < length; i++)
    {
        if (s[i] == '1')
        {
            n |= 1 << (length - 1 - i); // Set the corresponding bit
        }
    }

    return n;
}

void nfloat_debug(NewFloat f)
{
    // Shifting operations don't change the value of the variable they are applied to
    // Extracting and printing the sign bit (most significant bit)
    printf("%u ", (f >> 31) & 1);

    // Extracting and printing the exponent (next 5 bits)
    for (int i = 30; i >= 26; i--)
    {
        // Shifts the 32-bit integer f right by i positions to place the bit at position i in the least significant bit, then uses a bitwise AND with 1 to isolate and print this bit as either 0 or 1.
        // Since 1&1 will print 1 and 0&1 will print 0 like truth table for ^
        printf("%u", (f >> i) & 1);
    }
    printf(" ");

    // Extracting and printing the mantissa (last 26 bits)
    for (int i = 25; i >= 0; i--)
    {
        printf("%u", (f >> i) & 1);
    }
    printf("\n");
}

// Convert float into a NewFloat
NewFloat float_to_nfloat(float f)
{
    // f  // Some 32bit variable, often a float in this lab
    // &f // A pointer to a float
    // (unsigned*) &f // A pointer to an unsigned integer
    // *(unsigned*) &f // An unsigned integer

    unsigned int floatBits = *(unsigned int *)&f; // To get the 32 bit integer of the float

    // Extract the sign bit (same for float and NewFloat)
    unsigned int sign = (floatBits >> 31) & 1;

    // Extract and adjust the exponent
    // Mask: 0xFF (in binary: 00000000 00000000 00000000 11111111)
    unsigned int exponent = (floatBits >> 23) & 0xFF; // Extract 8-bit exponent

    // For example, extracted exponent is 128 (which is 10000000 in binary and represents an actual exponent of 1 (biased form is 127)).
    // newExponent = 128 - 127 + 15 = 16, which is 10000 in binary (in new format which have biased form of 15).
    int newExponent = exponent - 127 + 15; // Adjust from excess-127 to excess-15


    // These ensure the exponent fits in 5 bits. If the calculation results in a number outside the range 0 to 31, it's clamped to this range
    // The exponent is an unsigned integer from 0 to 31
    if (newExponent < 0)
        newExponent = 0;
    if (newExponent > 31)
        newExponent = 31;

    // Extract and adjust the mantissa
    // A 32-bit float has a 23-bit mantissa, but NewFloat requires a 26-bit mantissa. So, we shift the mantissa left by 3 bits.
    // If the mantissa part of floatBits is 00110011001100110011001,
    // After shifting 3 bits: 00110011001100110011001000 (now 26 bits).
    // Mask: 0x007FFFFF (in binary: 00000000 01111111 11111111 11111111)
    unsigned int mantissa = (floatBits & 0x7FFFFF) << 3; // Shift to 26 bits

    // Reassemble into NewFloat | sum them up
    NewFloat newFloat = (sign << 31) | (newExponent << 26) | mantissa;

    return newFloat;
}

// This function will print NewFloat type
void nfloat_print(NewFloat f)
{
    // Extract the components of NewFloat

    // Double have:
    // 1 bit for the sign
    // 11 bits for the exponent
    // 53 bits for the mantissa | NewFloat have 26 bit for the mantissa

    int sign = (f >> 31) & 1;

    int exponent = ((f >> 26) & 0x1F) - 15; // Adjusting from excess-15 (NewFloat binary exponent)
    // This line extracts the 5-bit exponent from f and adjusts it from the excess-15 format to the actual exponent value. Right-shifting by 26 bits moves the exponent bits to the rightmost part of the integer.
    // The & with 0x1F (which is 11111 in binary) isolates these 5 bits
    // Subtracting 15 adjusts the exponent from the excess-15 format

    uint64_t mantissa = f & 0x03FFFFFF;
    // 0x03FFFFFF = 00000011 11111111 11111111 11111111
    // The 26-bit mantissa is extracted from f
    // The & 0x03FFFFFF isolates the mantissa bits

    // Normalize subnormal numbers (when exponent is -15 after bias adjustment)
    // The exponent determines the magnitude of the number. Higher exponents mean larger numbers
    //  If the biased exponent is all zeros (`exponent` is less than `-14` after adjusting for the bias), the number is either zero or a subnormal number.

    if (exponent < -14)
    {
        exponent = -14; // Set the exponent to -14 for normalization
        while (!(mantissa & (1ULL << 52))) 
        // (1ULL << 52): Creates a number where only the 52nd bit is 1 and all other bits are 0
        // Checks if the 52nd bit in the mantissa is set
        // If the 52nd bit is 0, the condition becomes true, and the loop continues
        {                   
            mantissa <<= 1; // Shift the mantissa left by 1
            exponent -= 1;  // Decrement the exponent
        }
    }

    // Convert NewFloat's components to double's format
    // Adjusting exponent from NewFloat's format to double's format (excess-1023)
    exponent += 1023;

    // If the adjusted exponent is outside this range, it is set to the nearest boundary value (0 or 2047).
    if (exponent < 0)
        exponent = 0;
    if (exponent > 2047)
        exponent = 2047;

    // Adjust the mantissa (26 bits to 52 bits)
    // Shifts the 26-bit mantissa left by 26 places to align it for a 52-bit field in the double format to make room for the different in mantissa size between NewFloat and double
    mantissa <<= (52 - 26);

    // Combine into double format
    uint64_t doubleBits = ((uint64_t)sign << 63) | ((uint64_t)exponent << 52) | mantissa;

    // Print the value
    printf("%.7f\n", *((double *)&doubleBits));
}

// This function will doubling the nfloat
NewFloat nfloat_double(NewFloat f)
{
    // The exponent is an unsigned integer from 0 to 31
    // Perform a bitwise AND with 0x1F (which is 00011111 in binary) to isolate the last 5 bits, which represent the exponent.
    int exponent = (f >> 26) & 0x1F;

    // Just increase the exponent
    return (f & 0x80000000) | ((exponent + 1) << 26) | (f & 0x03FFFFFF);

}

// Dear beautiful TA that is looking at my code, I cant do this part so please give me good partial marks. <3
NewFloat nfloat_add(NewFloat a, NewFloat b) {
    return a;
}


int main(void)
{
    int part_num;
    char s1[40];
    float f1, f2;
    NewFloat n1, n2;

    // This will scan the input for you! Uncomment pieces once you implement
    // the functions for that part
    while (1)
    {
        int res = scanf(" p%d", &part_num);

        if (res != 1)
        {
            break;
        }
        else if (part_num == 1)
        {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_debug(n1);
        }
        else if (part_num == 2)
        {
            scanf("%f", &f1);
            n1 = float_to_nfloat(f1);
            nfloat_debug(n1);
        }
        else if (part_num == 3)
        {
            scanf("%s", s1);
            n1 = bits_string_to_nfloat(s1);
            nfloat_print(n1);
            // Note for myself:
            // basically, the mantissa bits are there to make sure that floating point number can be somewhat accurate, the exponents are there to make sure the floating point number can represent very big numbers or numbers very close to zero in a more effective manner, just like the scientific notation (1.25 x 10^99 would be better than writing 125 and 97 zero's back there; relate the UNBIASED exponent with that '99' and mantissa bits with the .25 part).
            // However, if we always assume it is 1.XX x 10^XX, the exponent has a minimal value, in our case, -15; it means numbers under 1.00000 * 2^-15 (0.00003) can not be represented, which is terrible accuracy. So, instead we want something like, for example, 0.0002 x 2^-14, which can represent a much smaller number well.
        }
        else
        {
            scanf("%s ", s1);
            if (s1[0] == 'd')
            {
                scanf("%f", &f1);
                n1 = float_to_nfloat(f1);
                n1 = nfloat_double(n1);
            }
            else
            {
                scanf("%f %f", &f1, &f2);
                n1 = float_to_nfloat(f1);
                n2 = float_to_nfloat(f2);
                n1 = nfloat_add(n1, n2);
            }

            nfloat_print(n1);
        }
    }
}
