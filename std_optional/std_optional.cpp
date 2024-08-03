#include <iostream>
#include <optional>
#include <string>

/*
* createString function creates a string if the parameter 'create' is passed as true. If the parameter is passed as 'false'
* it will not create a string and return 'nullopt' which means that no string is returned from the function.
*/
std::optional<std::string> createString(const bool create)
{
    if (create) {
        // Create and return a string from a function.
        return "A quick brown fox jumps over a lazy dog. ";
    }

    // Return a 'nullopt' which means that no value is returned from the function.
    return std::nullopt;
}

int main()
{
    std::cout << "Demonstration of std::optional in C++ ... \n\n";

    auto res1 = createString(true);       // Calling createString function with 'true'. It will return a string.
    if (res1.has_value()) {
        std::cout << "String returned from function createString() ... \n\n";
    }

    auto res2 = createString(false);      // Calling createString function with 'false'. It will not return a string.
    if (!res2.has_value()) {
        std::cout << "No string returned from function createString() ... \n\n";
    }

    return 0;
}



