#include <iostream>

/*
* A 'consteval' function which return the square of the input 'x'. This function will be evaluated at compile time
* always. The input parameter passed must be a constant.
*/
consteval int func1(int x)
{
    return x * x;
}

/*
* A 'constexpr' function which return the square of the input 'x'. This function can be evaluated either at compile time
* or at runtime depending upon the conditions of the input parameter and output storage parameter.
*/
constexpr int func2(int x)
{
    return x * x;
}

int main()
{
    std::cout << "Demonstration of consteval and constexpr functions in C++ ... \n\n";

    // Using 'consteval' function func1 by passing a constant value '3'. This function will be evaluated at 
    // 'compile time'.
    int a = func1(3);

    // Cannot use func1 by passing a variable as input parameter. Always a compilation error.
    // a = func1(a);

    // Using 'constexpr' function func2 by passing a constant value '4'. This function will be evaluated at 
    // 'runtime time' because the return value of the function is being stored in a variable.
    int b = func2(4);

    // Using 'constexpr' function func2 by passing a constant value '5'. This function will be evaluated at 
    // 'compile time' because the return value of the function is being stored in a constexpr attribute.
    constexpr int c = func2(5);

    // Using 'constexpr' function func2 by passing a variable 'a'. This function will be evaluated at 
    // 'runtime time' because the input parameter of the function is variable.
    int d = func2(a);

    std::cout << a << " " << b << " " << c << " " << d << "\n\n";

    return 0;
}

