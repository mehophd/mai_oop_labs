#include <iostream>
#include <string>
#include "bitstring.h"
#include <stdexcept>

int main() {
    std::string s1, s2;

    std::cout << "Введите первый BitString: ";
    std::cin >> s1;
    std::cout << "Введите второй BitString: ";
    std::cin >> s2;

    try {
        BitString bs1(s1);
        BitString bs2(s2);

        std::cout << "BitString 1: ";
        bs1.print(std::cout);
        std::cout << std::endl;

        std::cout << "BitString 2: ";
        bs2.print(std::cout);
        std::cout << std::endl;

        BitString sum = BitString::add(bs1, bs2);
        std::cout << "Сумма (bs1 + bs2): ";
        sum.print(std::cout);
        std::cout << std::endl;

        if (bs1.is_greater(bs2) || bs1.equals(bs2)) {
            BitString diff = BitString::subtract(bs1, bs2);
            std::cout << "Разница (bs1 - bs2): ";
            diff.print(std::cout);
            std::cout << std::endl;
        } else {
            std::cout << "Ошибка (отрицательный результат)" << std::endl;
        }

        BitString and_result = BitString::bit_and(bs1, bs2);
        std::cout << "AND (bs1 & bs2): ";
        and_result.print(std::cout);
        std::cout << std::endl;

        BitString or_result = BitString::bit_or(bs1, bs2);
        std::cout << "OR (bs1 | bs2): ";
        or_result.print(std::cout);
        std::cout << std::endl;

        BitString xor_result = BitString::bit_xor(bs1, bs2);
        std::cout << "XOR (bs1 ^ bs2): ";
        xor_result.print(std::cout);
        std::cout << std::endl;

        BitString not_bs1 = bs1.bit_not();
        std::cout << "NOT (bs1): ";
        not_bs1.print(std::cout);
        std::cout << std::endl;

        BitString not_bs2 = bs2.bit_not();
        std::cout << "NOT (bs2): ";
        not_bs2.print(std::cout);
        std::cout << std::endl;

        std::cout << "bs1 равен bs2: " << (bs1.equals(bs2) ? "true" : "false") << std::endl;
        std::cout << "bs1 больше bs2: " << (bs1.is_greater(bs2) ? "true" : "false") << std::endl;
        std::cout << "bs1 меньше bs2: " << (bs1.is_less(bs2) ? "true" : "false") << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}