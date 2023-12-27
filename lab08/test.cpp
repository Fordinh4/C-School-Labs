#include <stdio.h>
#include <stdint.h>

typedef uint32_t NewFloat;

void nfloat_print(NewFloat f){
    // Extract the components of NewFloat
    int sign = (f >> 31) & 1;
    int exponent = ((f >> 26) & 0x1F) - 15; // Adjusting from excess-15 (NewFloat binary exponent)
    uint64_t mantissa = f & 0x03FFFFFF; // The 26-bit mantissa is extracted from f

    // Normalize subnormal numbers (when exponent is -15 after bias adjustment)
    if (exponent < -14) {
        exponent = -14; // Set the exponent to -14 for normalization
        while (!(mantissa & (1ULL << 52))) { // While the mantissa is not normalized
            mantissa <<= 1; // Shift the mantissa left by 1
            exponent -= 1;  // Decrement the exponent
        }
    }
    
    // Adjust exponent for double's format (excess-1023)
    exponent += 1023;

    // If the adjusted exponent is outside this range, it is set to the nearest boundary value (0 or 2047).
    if (exponent < 0) exponent = 0;
    if (exponent > 2047) exponent = 2047;

    // Shift the 26-bit mantissa left by 26 places to align it for a 52-bit field in the double format
    mantissa <<= (52 - 26);

    // Combine into double format
    uint64_t doubleBits = ((uint64_t)sign << 63) | ((uint64_t)exponent << 52) | mantissa;

    // Print the value
    printf("%.7f\n", *((double*)&doubleBits));
}

int main() {
    NewFloat examples[] = {
        0x009FFC00,  // 0.0009765
        0x80000400,  // -0.0000000
        0x8194F42A,  // -0.0002843
        0x50FDC12F,   // 39.8449087
        // 00010011111111111111000000000000,10000000000000000000010000000000,10001100101010000111110000101010,01010000111110110000100101111110,
    };

    for (int i = 0; i < 4; i++) {
        nfloat_print(examples[i]);
    }

    return 0;
}
