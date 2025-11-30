#include <iostream>
#include <functional>
#include <list>

static int add(const int a, const int b) {
    return a + b;
}

class MyClass
{
public:
    MyClass() = default;

    void printData() {
        std::cout << "Instance " << this << " is printing data. " << std::endl;
    }
};

int main()
{
    std::cout << "Demonstration of std::bind in C++ ... \n";

    // Bind the 'add' function to the function arguments '22' and '33'. The std::bind will return a callable function object
    // which can be called later.
    auto callable1 = std::bind(add, 22, 33);
    auto result1 = callable1();
    std::cout << "'add' function result: " << result1 << std::endl;

    // Bind the 'add' function to the function parameter placeholders. The std::bind will return a callable function object
    // which can be called later. The parameters can be passed when calling the callable function object.
    auto callable2 = std::bind(add, std::placeholders::_1, std::placeholders::_2);
    auto result2 = callable2(1,2);
    std::cout << "'add' function result: " << result2 << std::endl << std::endl;

    // Bind the 'MyClass::printData' function to function parameter placeholders. The std::bind will return a callable function 
    // object which can be called later. The parameters can be passed when calling the callable function object.
    MyClass obj1, obj2;
    auto callable3 = std::bind(&MyClass::printData, std::placeholders::_1);
    callable3(&obj1);   // printData() of obj1 will be called.
    callable3(&obj2);   // printData() of obj2 will be called.
    std::cout << std::endl;

    // Bind the 'MyClass::printData' function to specific objects. The std::bind will return a callable function which are 
    // stored in a list. The function callable objects can be called later by iterating over the list.
    std::list<std::function<void()>> listOfCallableFunctionObjects;
    listOfCallableFunctionObjects.push_back(std::bind(&MyClass::printData, &obj1));
    listOfCallableFunctionObjects.push_back(std::bind(&MyClass::printData, &obj2));
    for (auto &f : listOfCallableFunctionObjects) {
        f();
    }

    return 0;
}
