#include <iostream>
#include <functional>

// A function which takes two integers, add them and return the result.
int func1(int a, int b) {
    std::cout << "Function 1 (addition) called ... \n";
    return a + b;
}

// A function which takes two integers, multiply them and return the result.
int func2(int a, int b) {
    std::cout << "Function 2 (multiplication) called ... \n";
    return a * b;
}

// A function which takes another function as an argument and calls it.
void func3(std::function<int(int, int)> f) {
    std::cout << "Function 3 called ... \n";
    f(3, 3);
}

int main()
{
    std::cout << "Demonstration of std::function in C++ ... \n\n";

    // Creating a function wrapper which 'wraps' or stores func1.
    std::function<int(int, int)> func = func1;

    // Call the funcation wrapper 'func'. It will call the function stored in it (func1).
    int res = func(1, 2);

    // Update the function wrapper 'func' which now 'wraps' or stores func2.
    func = func2;

    // Call the funcation wrapper 'func'. It will call the function stored in it (func2).
    res = func(1, 2);

    // Call a function 'func3' which takes a function wrapper as an argument and calls it.
    func3(func);

    return 0;
}



