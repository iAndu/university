#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Produs {
private:
	string denProd;
	float pretProd;

public:
	Produs() { }
	Produs(const string den, const float pret = 0) : denProd(den), pretProd(pret) { }
	Produs(const Produs &obj) : denProd(obj.denProd), pretProd(obj.pretProd) { }
	~Produs() { }
	string GetName() const { return denProd; }
};

class Data {
public:
	int zi, luna, an;
	Data() { }
	Data(const int z, const int l, const int a) : zi(z), luna(l), an(a) { }
	Data(const Data &obj) : zi(obj.zi), luna(obj.luna), an(obj.an) { }
	~Data() { }
	bool operator==(const Data &obj) {
		return zi == obj.zi && luna == obj.luna && an == obj.an;
	}
};

class Comanda {
private:
	int Num, nrPortii;
	Produs Prod;
	Data data;

public:
	static int nrComenzi;
	Comanda() { ++nrComenzi; }
	Comanda(const string nume, const int portii, const int z = 21, const int l = 5, const int a = 2017)
		: Prod(nume), nrPortii(portii), data(z, l, a) {
		Num = ++nrComenzi;
	}
	Comanda(const Comanda &obj) : Prod(obj.Prod.GetName()), nrPortii(obj.nrPortii), data(obj.data) {
		Num = ++nrComenzi;
	}
	~Comanda() { }

	Comanda& operator=(const Comanda &obj) {
		nrPortii = obj.nrPortii;
		Prod = obj.Prod;
		data = obj.data;

		return *this;
	}

	Comanda operator+(const int val) {
		Comanda aux = *this;
		aux.nrPortii += val;

		return aux;
	}

	Comanda operator++(int) {
		Comanda aux = *this;
		++nrPortii;

		return aux;
	}

	virtual void del() {
		nrPortii = 0;
	}

	Data GetData() const { return data; }
	Produs GetProd() const { return Prod; }
	friend ostream& operator<<(ostream &out, const Comanda &obj);
	friend istream& operator>>(istream &in, Comanda &obj);
};

istream& operator>>(istream &in, Comanda &obj) {
	string den;
	in >> den;
	obj.Prod = Produs(den);
	in >> obj.nrPortii >> obj.data.zi >> obj.data.luna >> obj.data.an;
	obj.Num = ++Comanda::nrComenzi;

	return in;
}

ostream& operator<<(ostream &out, const Comanda &obj) {
	out << obj.Num << ' ' << obj.Prod.GetName() << ' ' << obj.nrPortii << '/' << obj.data.zi << '/' << obj.data.luna << '/'
		 << obj.data.an << '\n';

	return out;
}

class Ospatar {
private:
	string Nume;
	Comanda *comenzi;
	int nrComenzi, varsta;
	char gen;

public:
	Ospatar() { }
	Ospatar(const string str, Comanda *ptr, const int com, const char g, const int age) : Nume(str), comenzi(ptr), nrComenzi(com), gen(g), varsta(age) { }
	Ospatar(const Ospatar &obj) { }
	~Ospatar() { }

	friend ostream& operator<<(ostream &out, const Ospatar &obj);
	bool operator>(const Ospatar &obj) const {
		return nrComenzi > obj.nrComenzi;
	}
	bool operator==(const Ospatar &obj) const {
		return nrComenzi == obj.nrComenzi;
	}
	string nume() const { return Nume; }

};

ostream& operator<<(ostream &out, const Ospatar &obj) {
	out << obj.Nume << ' ' << obj.nrComenzi << ' ' << obj.varsta << ' ' << obj.gen << '\n';

	return out;
}

int Comanda::nrComenzi = 0;

class ComSpec : virtual public Comanda {
private:
	string ObsC;
	float pretSupl;

public:
	ComSpec() { }
	ComSpec(const string obs, const float pret) : ObsC(obs), pretSupl(pret) { }
	ComSpec(const ComSpec &obj) { }
	~ComSpec() { }
};

class ComOnline : virtual public Comanda {
private:
	string adrLivr;
	int comLivr;

public:
	ComOnline() { }
	ComOnline(const string adr, const int com) : adrLivr(adr), comLivr(com) { }
	ComOnline(const ComOnline &obj) { }
	~ComOnline() { }
};

class ComSpecOnline : public ComSpec, public ComOnline {

};

int main() {
	Produs meniu[4] = { Produs("frigarui", 30), Produs("cola",7.5), Produs("cafea",5) };
	Comanda c1("frigarui", 2, 31, 5, 2016), c2("cola",3), c3("cafea",1), c4 = c2, c5;
	c3 = c3 + 4; // se comanda încă 4 cafele
	c2++; // se mai comandă o cola
	c1.del(); //se anulează comanda c1
	cin >> c5; //se citește comanda c5
	cout << c4 << endl << c5; //se afișează comanzile c4 și c5
	Comanda *com1 = new Comanda[4], *com2 = new Comanda[4];
	com1[0] = c1; com1[1] = c2; com1[2] = c3; com2[0] = c4; com2[1] = c5;
	Ospatar o1("Ionescu",com1,3,'M',25), o2("Popescu",com2,2,'F',30);
	cout << o1 << o2;
	if (o2 > o1) cout << "Ospatarul " << o2.nume() << "a servit mai multe comenzi decat ospatarul " << o1.nume() << endl;
	else if (o2 == o1) cout << "Numar egal de comenzi intre ospatarii " << o2.nume() << "si " << o1.nume() << endl;
	else cout << "Ospatarul " << o2.nume() << "a servit mai puține comenzi decat ospatarul " << o1.nume() << endl;

	vector<Comanda> vec;
	vec.push_back(c1);
	vec.push_back(c2);
	vec.push_back(c3);
	vec.push_back(c4);
	vec.push_back(c5);

	for (auto i : vec)
		if (i.GetData() == Data(31, 5, 2016))
			cout << i << '\n';

	int nr1 = 0, nr2 = 0;
	for (auto i : vec)
		if (i.GetProd().GetName() == "papanasi" && i.GetData().luna == 5 && i.GetData().an == 2016)
			++nr1;
		else if (i.GetProd().GetName() == "papanasi cu nuca de cocos" && i.GetData().luna == 5 && i.GetData().an == 2016)
			++nr2;

	cout << "Papanasi: " << nr1 << '\n' << "Papanasi cu nuca de cocos: " << nr2 << '\n';

	return 0;
}