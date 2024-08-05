#include <iostream>
#include <ranges>

int main()
{
    std::cout << "Demonstration of std::views in C++ ... \n\n";

    // Declaration of an input array containing integer elements.
    const int32_t arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // A lambda expression to check if the input integer is even or not.
    auto isEven = [](int32_t i) {
        if (i % 2 == 0) {
            return true;
        }
        return false;
    };

    // A lambda expression to check if the input integer is odd or not.
    auto isOdd = [](int32_t i) {
        if (i % 2 != 0) {
            return true;
        }
        return false;
    };

    // A lambda expression to return the square of input integer.
    auto performSquare = [](int32_t i) {
        return (i * i);
    };


    // Display input array.
    std::cout << "Input array: ";
    for (auto x : arr1) {
        std::cout << x << " ";
    }

    std::cout << "\n\n";


    // Using std::views::filter to view even values from array.
    std::cout << "Using std::views::filter to view even values from array: ";
    for (auto x : arr1 | std::views::filter(isEven)) {
        std::cout << x << " ";
    }

    std::cout << "\n\n";


    // Using std::views::filter to view odd values from array.
    std::cout << "Using std::views::filter to view odd values from array: ";
    for (auto x : arr1 | std::views::filter(isOdd)) {
        std::cout << x << " ";
    }

    std::cout << "\n\n";


    // Using std::views::transform to perform square operation on elements of input array.
    std::cout << "Using std::views::transform to perform square operation on elements of input array: ";
    for (auto x : std::views::transform(arr1, performSquare)) {
        std::cout << x << " ";
    }

    std::cout << "\n\n";


    // Using std::views::filter and std::views::transform to perform square operation on even elements of input array.
    std::cout << "Using std::views::filter and std::views::transform to perform square operation on even elements of "
                 "input array: ";
    for (auto x : std::views::transform(std::views::filter(arr1, isEven), performSquare)) {
        std::cout << x << " ";
    }

    std::cout << "\n\n";

    return 0;
}


