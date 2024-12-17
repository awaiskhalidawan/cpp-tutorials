#include <iostream>

template<class T>
class A
{
private:
    std::unique_ptr<T> e{nullptr};

public:
    A() 
    {
        // Template type of this class must be an arithmetic type i.e. (int, float, double, etc.)
        // A compilation error will be thrown if the type is other than arithmetic type.
        static_assert(std::is_arithmetic_v<T>);

        e = std::make_unique<T>();
    }

    ~A() 
    {
        e.reset(nullptr);
    }
};

int main()
{
    std::cout << "Demonstration of std::is_arithmetic type trait in C++ ... \n\n";

    A<int> obj;             // Creating an object of class A with type integer.

    //A<std::string> obj2;    // Creating an object of class A with type std::string. (This will be a COMPILATION ERROR as
                            // the type of class A is not of arithmetic type).

    return 0;
}

