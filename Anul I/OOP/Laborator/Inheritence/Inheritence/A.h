#ifndef A_H
#define A_H

#include <iostream>

class A
{
public:
	int xA;
	A()
	{
		std::cout << "Constructor A\n";
	}
	A(const A &obj)
	{
		std::cout << "Copy constructor A\n";
	}
	~A()
	{
		std::cout << "Destructor A\n";
	}

protected:
	int yA;

private:
	int zA;
};

#endif