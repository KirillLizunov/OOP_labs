#include "sol.h"  

std::string replacer(int n, char old_Value, char new_Value,  std::string text) {
    unsigned int counter {0};
    unsigned int count_symbol {0};

    for (int size_t = 0; size_t < text.size(); ++size_t){
        count_symbol++;
    }
    if (n <= 0 || n > count_symbol){
        return text;
        }
    for (int i = 0; i < text.size(); ++i) {  
        if (text[i] == old_Value) {
            counter ++;
        }
        if (counter == n) {
            text[i] = new_Value;
            counter = 0;
        }
    }

    return text;
}
