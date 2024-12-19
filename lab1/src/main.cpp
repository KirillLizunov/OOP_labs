#include "sol.h"
#include <iostream>


int main(){

    char old_Value;
    char new_Value;
    int n;
    std::string text;
    std::cout << "Введите n ";
    std::cin >> n;
    std::cout << "Введите old_Value ";
    std::cin >> old_Value;
    std::cout << "Введите new_Value ";
    std::cin >> new_Value;
    std::cin.ignore();
    std::cout << "Введите text ";
    std::getline(std::cin, text);
    std::cout << replacer(n, old_Value, new_Value, text) << std::endl;

    return 0;

}
