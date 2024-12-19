#include <iostream>
#include "include/memory_resource.h"
#include "include/list.h"

struct ComplexType {
    int a;
    double b;
    std::string c;

    ComplexType(int x, double y, const std::string& z) : a(x), b(y), c(z) {}
};

int main() {
    constexpr std::size_t memory_size = 1024;

    FixedBlockMemoryResource resource(memory_size);

    List<int> int_list(&resource);
    int_list.push_back(10);
    int_list.push_back(20);

    for (auto& val : int_list) {
        std::cout << val << " ";
    }

    List<ComplexType> complex_list(&resource);
    complex_list.push_back({1, 2.5, "test"});

    for (auto& val : complex_list) {
        std::cout << val.a << ", " << val.b << ", " << val.c << "\n";
    }

    return 0;
}