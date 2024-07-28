#include <iostream>

class Class1
{
public:
    // Copy assignment operator is deleted.
    Class1& operator=(const Class1& obj) = delete;

};

class Class2
{
public:
    // Non-throwing copy assignment operator is available
    Class2& operator=(const Class2& obj) noexcept
    {

    }
};

int main()
{
    std::cout << "Demonstration of std::is_copy_assignable, is_nothrow_copy_assignable and is_trivially_copy_assignable"
        " in C++ ... \n\n";

    // Class1 has copy assignable operator deleted so output will be false.
    std::cout << "Class1 is_copy_assignable: " << std::boolalpha << std::is_copy_assignable_v<Class1> << std::endl;

    // Class1 has copy assignable operator deleted so output will be false.
    std::cout << "Class1 is_nothrow_copy_assignable: " << std::boolalpha << std::is_nothrow_copy_assignable_v<Class1>
        << std::endl;

    // Class1 has copy assignable operator deleted so output will be false.
    std::cout << "Class1 is_trivially_copy_assignable_v: " << std::boolalpha << std::is_trivially_copy_assignable_v<Class1>
        << std::endl << std::endl;


    // Class2 has copy assignable operator defined so output will be true.
    std::cout << "Class2 is_copy_assignable: " << std::boolalpha << std::is_copy_assignable_v<Class2> << std::endl;

    // Class2 has copy assignable operator defined with 'noexcept' which means it will not throw the exception. The
    // output will be true.
    std::cout << "Class2 is_nothrow_copy_assignable: " << std::boolalpha << std::is_nothrow_copy_assignable_v<Class2> 
        << std::endl;

    // Class2 has copy assignable operator defined which means its not trivially copy assignable. The output will be 
    // false.
    std::cout << "Class2 is_trivially_copy_assignable_v: " << std::boolalpha << std::is_trivially_copy_assignable_v<Class2>
        << std::endl << std::endl;

    return 0;
}