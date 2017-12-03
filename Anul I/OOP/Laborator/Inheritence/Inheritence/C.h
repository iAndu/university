#ifndef C_H
#define C_H

#include <iostream>

class C
{
public:
	//A obj;
	//B obj2;

	C()
	{
		std::cout << "Constructor C\n";
	}
	C(const C &obj)
	{
		std::cout << "Copy constructor C\n";
	}
	~C()
	{
		std::cout << "Destructor C\n";
	}
};

#endif