#ifndef PIZZABASE_H
#define PIZZABASE_H

#include "Ingrediente.h"

class PizzaBase 
{

protected:
	int m_NrIngrediente;
	E_Ingrediente m_Ingrediente[7];

	void AdaugaIngredient(E_Ingrediente);

public:
	PizzaBase();

	virtual int CalculeazaPret() = 0;
};

#endif