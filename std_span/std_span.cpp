#include <iostream>
#include <vector>
#include <span>

int main()
{
    std::cout << "Demonstration of std::span in C++ ... \n\n";

    // Creating a fixed size array of size 10 and a span from it.
    uint32_t arr1[10] = { 0 };
    std::span<uint32_t> sp1(arr1);

    for (auto& it : sp1) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    // Creating a dynamically allocated array of size 10 and a span from it. Updating the elements of array using span.
    uint32_t* arr2 = new uint32_t[10];
    std::span<uint32_t> sp2(arr2, 10);

    for (auto& it : sp2) {
        it = 1;
        std::cout << it << " ";
    }
    std::cout << std::endl;

    // Creating a vector of size 10 and a span from it. Updating the elements of array using span.
    std::vector<uint32_t> vec3(10);
    std::span<uint32_t> sp3(vec3);
    for (auto& it : sp3) {
        it = 10;
        std::cout << it << " ";
    }

    std::cout << std::endl;

    return 0;
}