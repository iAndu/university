#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ingredient;

class Manager {
private:
	static vector<Ingredient> ing;

public:
	static void AddIng(const Ingredient &obj) { ing.push_back(obj); }
	static void RemoveIng(const Ingredient &obj) {
		for (auto i = ing.begin(); i != ing.end(); ++i)
			if (*i == obj) {
				ing.erase(i);
				return;
			}
	}
	static void ModifyIng(const Ingredient &obj1, const Ingredient &obj2) {
		for (auto i = ing.begin(); i != ing.end(); ++i)
			if (*i == obj1) {
				ing.erase(i);
				break;
			}
		ing.push_back(obj2);
	}
	static void ShowAvailableIngredients() {
		for (auto i : ing)
			cout << i << endl;
	}
};

vector<Ingredient> Manager::ing;

class Ingredient {
private:
	string denIng, masIng;
	double pretIng;
	int cantIng;

public:
	Ingredient(const string ing, const double pret, const int cant, const string mas) : 
		denIng(ing), pretIng(pret), cantIng(cant), masIng(mas) { Manager::AddIng(*this); }
	Ingredient() { }
	Ingredient(const Ingredient &obj) { *this = obj; Manager::AddIng(*this); }
	~Ingredient() { Manager::RemoveIng(*this); }
	Ingredient& operator=(const Ingredient &obj) {
		Manager::ModifyIng(*this, obj);
		denIng = obj.denIng;
		masIng = obj.masIng;
		pretIng = obj.pretIng;
		cantIng = obj.cantIng;
	}
	friend istream& operator>>(istream &in, Ingredient &obj) {
		in >> obj.denIng >> obj.pretIng >> obj.cantIng >> obj.masIng;
		Manager::AddIng(obj);

		return in;
	}
	Ingredient operator+(const int val) {
		Ingredient aux = *this;
		aux.cantIng += val;

		return aux;
	}
	Ingredient operator++(int) {
		Ingredient aux = *this;
		++cantIng;

		return aux;
	}
	void operator-=(const double val) {
		pretIng -= val;
	}
	void del() {
		cantIng = 0;
	}
	friend ostream& operator<<(ostream &out, const Ingredient &obj) {
		out << obj.denIng << ' ' << obj.pretIng << ' ' << obj.cantIng << ' ' << obj.masIng;

		return out;
	}
	template<class T>
	bool operator==(T &obj) const {
		return denIng == obj.denIng && pretIng == obj.pretIng && masIng == obj.masIng && cantIng == obj.cantIng;
	}
	double GetPrice() const { return pretIng; }
};

class Pizza {
protected:
	static int sortPizza;
	int codPizza, nringPizza;
	string denPizza;
	vector<Ingredient> ingPizza;
	bool vegPizza;

public:
	Pizza(const string den = "", Ingredient *lista = nullptr, const int nring = 0, const bool veg = false) : 
		denPizza(den), nringPizza(nring), vegPizza(veg) {
			codPizza = ++sortPizza;
			for (int i = 0; i < nringPizza; ++i)
				ingPizza.push_back((lista[i]));
		}
	Pizza(vector<Ingredient> lista, const string den = "", const int nring = 0, const bool veg = false) : 
		denPizza(den), nringPizza(nring), vegPizza(veg) {
			codPizza = ++sortPizza;
			for (auto i : lista)
				ingPizza.push_back(i);
		}
	Pizza(const Pizza &obj) { *this = obj; ++sortPizza; }
	~Pizza() { --sortPizza; }
	Pizza& operator=(const Pizza &obj) {
		denPizza = obj.denPizza;
		nringPizza = obj.nringPizza;
		ingPizza = obj.ingPizza;
		vegPizza = obj.vegPizza;
	}
	Pizza operator-(const Ingredient &obj) const {
		Pizza aux = *this;
		for (auto i = aux.ingPizza.begin(); i != aux.ingPizza.end(); ++i)
			if (*i == obj) {
				aux.ingPizza.erase(i);
				return aux;
			}
		return aux;
	}
	Pizza operator+(const Ingredient &obj) const {
		Pizza aux = *this;
		aux.ingPizza.push_back(obj);

		return aux;
	}
	virtual string nume() const { return denPizza; }
	virtual double pret() const {
		double price = 0;
		for (auto i : ingPizza)
			price += i.GetPrice();
		return price * 1.5;
	}
	void nume(const string num) { denPizza = num; }
};

int Pizza::sortPizza;

class PizzaSpec : public Pizza {
private:
	vector<Ingredient> ingPizza;
	int nringPizza;

public:
	PizzaSpec() { }
	PizzaSpec(const string den, Ingredient *lista, const int nring, Ingredient *listaS, const int nringS) :
		Pizza(den, lista, nring, false), nringPizza(nringS) {
			for (int i = 0; i < nringPizza; ++i)
				ingPizza.push_back((listaS[i]));
		}
	PizzaSpec(const PizzaSpec &obj) : Pizza(obj.Pizza::ingPizza, obj.denPizza, obj.Pizza::nringPizza, obj.vegPizza) { *this = obj; }
	PizzaSpec& operator=(const PizzaSpec &obj) {
		ingPizza = obj.ingPizza;
		nringPizza = obj.nringPizza;
	}
	double pret() const {
		double price = Pizza::pret();
		for (auto i : ingPizza)
			price += i.GetPrice() * 1.5;
		return price;
	}
	PizzaSpec operator+(const Ingredient &obj) const {
		PizzaSpec aux = *this;
		aux.ingPizza.push_back(obj);

		return aux;
	}
	PizzaSpec operator-(const Ingredient &obj) const {
		PizzaSpec aux = *this;
		for (auto i = aux.ingPizza.begin(); i != aux.ingPizza.end(); ++i)
			if (*i == obj) {
				aux.ingPizza.erase(i);
				return aux;
			}
		return aux;
	}
};

class Bautura {
private:
	string denBaut;
	double pretBaut;

public:
	Bautura(const string den = "", const double pret = 0) : denBaut(den), pretBaut(pret) { }
	Bautura(const Bautura &obj) { *this = obj; }
	Bautura& operator=(const Bautura &obj) {
		denBaut = obj.denBaut;
		pretBaut = obj.pretBaut;
	}
	~Bautura() { }
};

class OfSpec : public Pizza {
private:
	Bautura drink;
};


int main() {
	vector<Ingredient> ing;

	Ingredient lista[5] = { Ingredient("piept de pui", 15, 1, "kg"), Ingredient("sare",0.75, 10, "gram"), Ingredient("salam",1.5,5, "felii"), lista[2], Ingredient() }, i1("sunca", 3, 2, "felii");
	cin >> lista[4]; // se citește un nou ingredient
	lista[3] = lista[3] + 3; // se adaugă 3 felii de salam la ingredient
	lista[1]++; // se adaugă un gram de sare la ingredient
	lista[0]-=2.5; // se scade o valoare din pretul ingredientului
	lista[2].del(); //ingredientul nu mai este disponibil
	for (int i=0; i<5; i++) cout<<"Ingredient: "<<lista[i]<<endl;
	Pizza p1 ("Rustica", lista, 4, false);	// se crează un sortiment nou de pizza 
	Pizza p2 = p1, p3; // se crează două sortimente noi de pizza, dintre care unul cu aceleași ingrediente ca pizza p1
	p2 = p2 - lista[2]; // se scoate ingredientul respectiv din rețeta sortimentului
	p3 = p2 + i1;	// se stabilește rețeta pizzei p3 din ingredientele pizzei p2 la care se adaugă ingredientul i1
	p3.nume("Prosciuto"); // este schimbată denumirea pizzei p3 
	cout<<"Pizza "<<p1.nume()<<" "<<p1.pret()<<" lei"<<endl;
	cout<<"Pizza "<<p2.nume()<<" "<<p2.pret()<<" lei"<<endl;
	cout<<"Pizza "<<p3.nume()<<" "<<p3.pret()<<" lei";

	return 0;
}