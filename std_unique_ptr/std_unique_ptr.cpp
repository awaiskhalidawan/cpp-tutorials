#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <memory>
#include <stdio.h>

struct A
{
    int a = 0;
    int b = 0;

    A() 
    {
        std::cout << this << " A() called ..." << std::endl;
    }

    ~A()
    {
        std::cout << this << " ~A() called ..." << std::endl;
    }
};

void customDeletor(A* a) 
{
    std::cout << a << " customDeletor() called ... " << std::endl;
    delete[] a;
}

void customFileDeletor(FILE* file)
{
    std::cout << file << " customFileDeletor() called ... " << std::endl;
    fclose(file);
    std::cout << "File closed successfully ... " << std::endl;
}

int main()
{    
    std::cout << "Demonstration of std::unique_ptr in C++ ... \n\n";

    // 1. Creating a unique pointer to a single object. The object will be deleted from heap once uptr1 goes out of scope.
    std::unique_ptr<A> uptr1 = std::make_unique<A>();
    std::cout << std::endl;

    // 2. Creating a unique pointer to an array of objects. The objects array will be deleted from heap once uptr2 goes 
    // out of scope.
    std::unique_ptr<A[]> uptr2 = std::make_unique<A[]>(10);
    std::cout << std::endl;

    // 3. Creating a unique pointer to an array of objects using the new operator. The objects array will be deleted from 
    // heap once uptr3 goes out of scope.
    std::unique_ptr<A[]> uptr3(new A[10]);
    std::cout << std::endl;

    // 4. Creating a unique pointer to an array of objects using the new operator and raw pointer. The objects array will 
    // be deleted from heap once uptr4 goes out of scope.
    A* a = new A[10];
    std::unique_ptr<A[]> uptr4(a);
    std::cout << std::endl;

    // 5. Creating a unique pointer to an array of objects using the new operator and custom deletor. The custom deletor 
    // will be called once uptr5 goes out of scope. In the custom deletor we will delete the memory.
    std::unique_ptr<A[], decltype(&customDeletor)> uptr5(new A[10], &customDeletor);
    std::cout << std::endl;

    // 6. Creating a unique pointer to FILE pointer to manage the life time of FILE. The custom deletor will be called 
    // once uptr6 goes out of scope. In the custom deletor, the file will be closed automatically.
    FILE* file = fopen("C:\\abc.txt", "rb");
    if (file) {
        std::cout << "File opened successfully ... " << std::endl;
        std::unique_ptr<FILE, decltype(&customFileDeletor)> uptr6(file, &customFileDeletor);
        std::cout << std::endl;
    }

    return 0;
}


