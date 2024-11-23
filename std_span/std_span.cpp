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

    // Creating subspans from span.
    // Create an array of N * S size.
    constexpr uint16_t N = 3;
    constexpr uint16_t S = 5;
    uint32_t data[N * S] = { 0 };

    // Create a span over data array.
    std::span<uint32_t> dataSpan(data);

    // Create total of S subspans each of size N.
    std::vector <std::span<uint32_t>> spanList;
    for (uint32_t i = 0; i < (N * S); i+=N) {
        auto subspan = dataSpan.subspan(i, N);
        spanList.push_back(subspan);
    }

    // Iterate over each span from span list and print the span.
    uint32_t c = 0;
    for (auto &span : spanList) {
        ++c;
        for (auto& it : span) {
            it = c;
            std::cout << it << " ";
        }
    }

    std::cout << std::endl;

    return 0;
}