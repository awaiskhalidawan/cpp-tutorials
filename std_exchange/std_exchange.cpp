#include <iostream>
#include <utility>

class myClass {
    
public:
    myClass() = delete;

    myClass(const uint32_t value) {
        a = value;
    }

    myClass(myClass&& other) noexcept {
        // Using std::exchange to move the value from other.a to this.a and setting other.a to zero.
        a = std::exchange(other.a, 0);
    }

    myClass& operator=(myClass&& other) noexcept {
        // Using std::exchange to move the value from other.a to this.a and setting other.a to zero.
        a = std::exchange(other.a, 0);
        return *this;
    }

    void print() const {
        std::cout << a << std::endl;
    }

private:
    uint32_t a {0};
};

void func() {
    std::cout << "func() called ..." << std::endl;
}

int main()
{
    std::cout << "Demonstration of std::exchange in C++ " << std::endl;
    
    // Example 1: Replace the values using std::exchange.
    uint32_t x = 2;
    uint32_t y = 10;
    uint32_t old_x = std::exchange(x, y);
    std::cout << x << " " << old_x << std::endl;

    // Example 2: Set the function pointer values using std::exchange.
    void(*functionPtr)();
    auto old_function_ptr = std::exchange(functionPtr, func);
    functionPtr();

    // Example 3: Moving class objects. Move constructor is using std::exchange to move the values from one object to other object.
    myClass obj1{10};
    std::cout << "obj1 value: ";
    obj1.print();
    myClass obj2 {std::move(obj1)};
    std::cout << "obj2 value: ";
    obj2.print();

    return 0;
}

