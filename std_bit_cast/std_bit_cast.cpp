#include <iostream>
#include <bit>
#include <array>
#include <string>

class MyClass
{
public:
    MyClass() = default;
    ~MyClass() = default;
    MyClass(const MyClass& obj) = default;

private:
    int x{ 0 };
    float y{ 0 };
};

struct MyStruct {
    int x;
    float y;
};

int main()
{
    std::cout << "Demonstration of std::bit_cast in C++ ... \n\n";

    // Create an integer with value (2) and cast it to float using std::bit_cast. std::bit_cast will interpret 
    // the bytes of integer as float. The bytes [0x02000000] (little-endian) converts to the float value 2.8026e-45.
    const int a = 2;
    const float b = std::bit_cast<float>(a);  
    std::cout << "Integer 'a' = " << a << std::endl;
    std::cout << "Float 'b' (created from the bytes of integer 'a') = " << b << std::endl; 

    // Create a structure and gets a copy of its memory bytes in an array using std::bit_cast. The std::bit_cast 
    // requires that the structure must be trivially copyable i.e. Its copy constructor must be compiler defined.
    // The size of the array will be 8 as structure object size is 8 bytes.
    MyStruct obj = { 1, 2.0 };
    auto obj_bin = std::bit_cast<std::array<uint8_t, sizeof(obj)>>(obj);
    std::cout << "structure object memory bytes size: " << obj_bin.size() << std::endl;

    // Create a class and gets all a copy its memory bytes in an array using std::bit_cast. The std::bit_cast 
    // requires that the class must be trivially copyable i.e. Its copy constructor must be compiler defined.
    // The size of the array will be 8 as class object size is 8 bytes.
    MyClass obj1;
    auto obj1_bin = std::bit_cast<std::array<uint8_t, sizeof(obj1)>>(obj1);
    std::cout << "class object memory bytes size: " << obj1_bin.size() << std::endl;

    return 0;
}


