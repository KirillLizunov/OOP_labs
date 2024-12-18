#include "BitString.h"
#include <iostream>

int main() {

    std::string input1, input2;
    std::cout << "Введите первую битовую строку (например, 1001101): ";
    std::cin >> input1;
    std::cout << "Введите вторую битовую строку (например, 1100110): ";
    std::cin >> input2;
    
    BitString bitStr1(input1);
    BitString bitStr2(input2);

    BitString result = bitStr1 + bitStr2;
    std::cout << "Результат сложения: " << result << std::endl;

    result = bitStr1 - bitStr2;
    std::cout << "Результат вычитания: " << result << std::endl;

    result = bitStr1 & bitStr2;
    std::cout << "Результат AND: " << result << std::endl;

    result = bitStr1 | bitStr2;
    std::cout << "Результат OR: " << result << std::endl;

    result = bitStr1 ^ bitStr2;
    std::cout << "Результат XOR: " << result << std::endl;

    result = ~bitStr1;
    std::cout << "Результат NOT первой строки: " << result << std::endl;

    return 0;
}