#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int reverse1(int x);
int reverse2(int x);
unsigned int powjuu(unsigned int x, unsigned int y);

int main(void) {
    printf("%d %d %d %d %d %d %d %d %d %d %d\n", powjuu(2, 0), powjuu(2, 1), powjuu(2, 2), powjuu(2, 3), powjuu(2, 4), powjuu(2, 5), powjuu(2, 6), powjuu(2, 7), powjuu(2, 8), powjuu(2, 9), powjuu(2, 10));
    printf("%d %d %d %d %d %d %d %d %d %d\n", powjuu(10, 0), powjuu(10, 1), powjuu(10, 2), powjuu(10, 3), powjuu(10, 4), powjuu(10, 5), powjuu(10, 6), powjuu(10, 7), powjuu(10, 8), powjuu(10, 9));
    printf("====\n");
    printf("%d %d\n", 123, reverse1(123));
    printf("%d %d\n", -123, reverse1(-123));
    printf("%d %d\n", -2147483412, reverse1(-2147483412));
    printf("%d %d\n", 2147483647, reverse1(2147483647));
    printf("%d %d\n", -2147483648, reverse1(-2147483648));
    printf("%d %d\n", 1111111111, reverse1(1111111111));
    printf("%d %d\n", 1111111192, reverse1(1111111192));
    printf("====\n");
    printf("%d %d\n", 123, reverse2(123));
    printf("%d %d\n", -123, reverse2(-123));
    printf("%d %d\n", -2147483412, reverse2(-2147483412));
    printf("%d %d\n", 2147483647, reverse2(2147483647));
    printf("%d %d\n", -2147483648, reverse2(-2147483648));
    printf("%d %d\n", 1111111111, reverse2(1111111111));
    printf("%d %d\n", 1111111192, reverse2(1111111192));
    return 0;
}

// taken from https://stackoverflow.com/a/26868762
unsigned int powjuu(unsigned int x, unsigned int y) {
    unsigned int z = 1;
    unsigned int base = x;
    while (y) {
        if (y & 1) {  // or y%2
            z *= base;
        }
        y >>= 1;  // or y /= 2
        base *= base;
    }
    return z;
}

int reverse2(int x) {
    int result = 0;
    int multiplier = x < 0 ? -1 : 1;
    int digits_count = 0;
    int digits[10] = {0};
    int overflow = 0;

    for (int i = 0; x != 0 && i < 10; i++) {
        digits[i] = abs(x % 10);
        x /= 10;
        digits_count++;
    }

    // printf("-> %d // %d %d %d %d %d %d %d %d %d %d\n", digits_count,
    // digits[0],digits[1],digits[2],digits[3],digits[4],digits[5],digits[6],digits[7],digits[8],digits[9]);

    if (digits_count == 10 && digits[0] >= 2) {
        if (digits[0] > 2) {
            overflow = 1;
        } else {
            unsigned int test = 0;
            int power = 100000000;
            for (int i = 1; i < 10; i++) {
                test += digits[i] * power;
                power /= 10;
            }
            overflow = (digits[0] * 1000000000) > (unsigned int)(INT_MAX + (multiplier == -1 ? 1 : 0)) - test;
        }
    }
    // –2147483648
    //  2147483647
    if (overflow == 0) {
        int power = powjuu(10, digits_count - 1);
        for (int i = 0; i < digits_count; i++) {
            result += digits[i] * power;
            power /= 10;
        }
    }

    return result * multiplier;
}

int reverse1(int x) {
    int result = 0;
    int multiplier = x < 0 ? -1 : 1;
    int digits_count = 0;
    int digits[10] = {0};

    for (int i = 0; x != 0 && i < 10; i++) {
        digits[i] = abs(x % 10);
        x /= 10;
        digits_count++;
    }

    // printf("-> %d // %d %d %d %d %d %d %d %d %d %d\n", digits_count,
    // digits[0],digits[1],digits[2],digits[3],digits[4],digits[5],digits[6],digits[7],digits[8],digits[9]);

    // –2147483648
    //  2147483647
    if (digits_count == 10 && (
        (digits[0] > 2) ||
        (digits[0] == 2 && digits[1] > 1) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] > 4) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] > 7) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] > 4) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] == 4 && digits[5] > 8) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] == 4 && digits[5] == 8 && digits[6] > 3) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] == 4 && digits[5] == 8 && digits[6] == 3 && digits[7] > 6) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] == 4 && digits[5] == 8 && digits[6] == 3 && digits[7] == 6 && digits[8] > 4) ||
        (digits[0] == 2 && digits[1] == 1 && digits[2] == 4 && digits[3] == 7 && digits[4] == 4 && digits[5] == 8 && digits[6] == 3 && digits[7] == 6 && digits[8] == 4 && digits[9] > (multiplier == -1 ? 8 : 7))
    )) {
        result = 0;
    } else {
        int power = powjuu(10, digits_count - 1);
        for (int i = 0; i < digits_count; i++) {
            
            result += digits[i] * power;
            power /= 10;
        }
    }

    return result * multiplier;
}