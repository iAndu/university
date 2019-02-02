#include "PizzaBase.h"
#include <iostream>

int PizzaBase :: CalculeazaPret()
{
	std :: cout << "Pizza Base\n";

	return 0;
}

void PizzaBase :: AdaugaIngredient(E_Ingrediente deAdaugat)
{
	m_Ingrediente[++this->m_NrIngrediente] = deAdaugat;
}

PizzaBase :: PizzaBase() : m_NrIngrediente(0)
{
	this->AdaugaIngredient(E_INGREDIENT_BLAT);
	this->AdaugaIngredient(E_INGREDIENT_SOS);
}