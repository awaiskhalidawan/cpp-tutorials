#include <iostream>

class myClass
{
private:
	uint32_t x{ 0 };

public:
	myClass()
	{
		std::cout << "Default constructor called ... " << this << "\n";
	}

	myClass(const uint32_t value) : x(value)
	{
		std::cout << "Overloaded default constructor 1 called ... " << this << "\n";
	}

	myClass(const uint32_t value1, const uint32_t value2) : x(value1 + value2)
	{
		std::cout << "Overloaded default constructor 2 called ... " << this << "\n";
	}

	myClass(myClass& obj)
	{
		std::cout << "Copy constructor called ... " << this << "\n";
		x = obj.x;
	}

	myClass(const myClass& obj)
	{
		std::cout << "Const copy constructor called ... " << this << "\n";
		x = obj.x;
	}

	myClass& operator=(const myClass& obj)
	{
		std::cout << "Copy operator called ... " << this << "\n";
		x = obj.x;
		return *this;
	}

	myClass(myClass&& obj) noexcept
	{
		std::cout << "Move constructor called ... " << this << "\n";
		x = obj.x;
	}

	myClass& operator=(myClass&& obj) noexcept
	{
		std::cout << "Move operator called ... " << this << "\n";
		x = obj.x;
	}

	~myClass()
	{
		std::cout << "Destructor called ... " << this << "\n";
	}

	void setValue(const uint32_t value) 
	{
		this->x = value;
	}
};

/*
* A wrapper function to create instances of class 'T' on heap. It 'forwards' the incoming arguments as it they are 
i.e. it keeps the value-category of the arguments as they are passed to any further functions inside the wrapper
function.
*/
template <typename T, typename... U>
std::shared_ptr<T> createInstance(U&&... args)
{
	std::cout << "createInstances() called ... " << std::endl;
	auto obj = std::make_shared<T>(std::forward<U>(args)...);
	std::cout << std::endl;
	return obj;
}

int main()
{
	std::cout << "Demonstration of std::forward in C++" << std::endl << std::endl;

	myClass a1(1);					// Creating an object of class 'myClass'.
	myClass& a2 = a1;				// Creating a non-const l-value reference of 'myClass'.
	const myClass& a3 = a1;			// Creating a const l-value reference of 'myClass'.

	std::cout << std::endl;

	// Creating different instances of myClass using std::forward using wrapper functions.
	auto obj1 = createInstance<myClass>(a2);			// Creating an instance of 'myClass' using non-const l-value ref.
	auto obj2 = createInstance<myClass>(a3);			// Creating an instance of 'myClass' using const l-value ref.
	auto obj3 = createInstance<myClass>(std::move(a1)); // Creating an instance of 'myClass' using r-value ref.
 	auto obj4 = createInstance<myClass>(2, 2);			// Creating an instance of 'myClass' using two r-value ref.

	return 0;
}

