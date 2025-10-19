#include "../include/euclid.h"

int euclid (int num1, int num2) {
    if (num1 < 0) {
        num1 = num1 * (-1);
    }
    if (num2 < 0) {
        num2 = num2 * (-1);
    }

    while (num1 != 0 && num2 != 0) {
        if (num1 > num2) {
            num1 = num1 % num2;
        } else {
            num2 = num2 % num1;
        }
    }
    return (num1 + num2);
}
