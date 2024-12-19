#include <iostream>
#include <string>

std::string replacer(int n, char old_Value, char new_Value, std::string text) {
    int count = 0;
    for (char &c : text) {
        if (c == old_Value) {
            if (count < n) {
                c = new_Value;
                count++;
            } else {
                break;
            }
        }
    }
    return text;
}