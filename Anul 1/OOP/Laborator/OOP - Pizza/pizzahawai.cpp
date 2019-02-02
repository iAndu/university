#include "PizzaHawai.h"
#include <iostream>


int PizzaHawai :: CalculeazaPret()
{
	int pret = 3;

	for (int i = 0; i < m_NrIngrediente; ++i)
		pret += m_Ingrediente[i];

	std :: cout << "Pizza Hawai\n";

	return pret;
}

PizzaHawai :: PizzaHawai()
{
	this->AdaugaIngredient(E_INGREDIENT_SUNCA);
	this->AdaugaIngredient(E_INGREDIENT_ANANAS);
}