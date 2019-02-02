#ifndef B_H
#define B_H

#include "A.h"
#include "C.h"
class B : public A
{
	void Nothing()
	{
		//xA++;
		//yA++;
		//zA++;
	}

public:
	//A obj;
	C obj2;
	B()
	{
		std::cout << "Constructor B\n";
	}
	B(const B &obj)
	{
		std::cout << "Copy constructor B\n";
	}
	~B()
	{
		std::cout << "Destructor B\n";
	}
};

#endif