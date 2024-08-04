#include <iostream>
#include <variant>
#include <string>

int main()
{
    std::cout << "Demonstration of std::variant in C++ ... \n\n";

    std::variant<int, std::string> var; // Declare a variant 'var'. It can hold either an int or a string at a time.

    var = "test string";      // Varient 'var' is holding a string 'test string'.
    var = 3;                  // Now Varient 'var' is holding and integer. The string value is not available anymore.

    try
    {
        // Trying to get integer value from varient 'var'. It will succeed as variant contains an integer value.
        std::cout << "Variant 'var' value is: " << std::get<int>(var) << "\n\n";
    }
    catch (std::bad_variant_access& ex)
    {
        std::cout << "An exception has occured while accessing the variant: " << ex.what() << "\n\n";
    }

    try 
    {
        // Trying to get string value from varient 'var'. It will fail as variant does not contain a string value.
        std::cout << "Variant 'var' value is: " << std::get<std::string>(var) << "\n\n";
    }
    catch (std::bad_variant_access& ex) 
    {
        std::cout << "An exception has occured while accessing the variant: " << ex.what() << "\n\n";
    }

    return 0;
}



