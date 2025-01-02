#include <iostream>
#include <expected>

// A function which performs a mathematical division operation and returns the result. A result can be a valid value or an
// unexpected result.
std::expected<double, std::string> performDivision(const double x, const double y) {
    if (y) {
        // Perform the division operation if the divisor is non-zero.
        return x / y;
    }

    // Return and unexpected error condition if the divisor is zero.
    return std::unexpected("Divisor cannot be zero ... ");
}

int main()
{
    std::cout << "Demonstration of std::expected in C++" << std::endl << std::endl;

    auto result = performDivision(10, 1);       // Call the function to perform the operation.

    if (result.has_value()) {                   // Check if the result has a valid value. Print the value.
        std::cout << "Result: " << result.value() << std::endl;
    }
    else {                      // If there are no valid values in the result than it contains an unexpected error value.
        std::cout << "An error occured while calling performDivision(): " << result.error() << std::endl;
    }

    return 0;
}


