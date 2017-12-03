#include <iostream>
#include "PizzaHawai.h"
#include "PizzaDiavola.h"

using namespace std;

int main()
{
	PizzaBase *VectorPizza[3];

	VectorPizza[0] = new PizzaHawai();
	VectorPizza[1] = new PizzaDiavola();
	VectorPizza[2] = new PizzaDiavola();

	for (int i = 0; i < 3; ++i)
		VectorPizza[i]->CalculeazaPret();

	cout << sizeof(PizzaBase) << '\n';


	return 0;
}