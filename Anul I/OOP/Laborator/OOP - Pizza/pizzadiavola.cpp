#include "PizzaDiavola.h"
#include <iostream>

int PizzaDiavola :: CalculeazaPret()
{
	int pret = 5;

	for (int i = 0; i < m_NrIngrediente; ++i)
		pret += m_Ingrediente[i];

	std::cout << "Pizza Diavola\n";

	return pret;
}

PizzaDiavola :: PizzaDiavola()
{
	this->AdaugaIngredient(E_INGREDIENT_SUNCA);
	this->AdaugaIngredient(E_INGREDIENT_SALAM);
}