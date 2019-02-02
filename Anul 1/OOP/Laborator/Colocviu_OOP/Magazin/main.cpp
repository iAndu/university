#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
	int day, month, year;
	Date(const int d = 0, const int m = 0, const int y = 0) : day(day), month(m), year(y) { }
	Date(const Date &obj) { *this = obj; }
	~Date() { }
	Date& operator=(const Date &obj) {
		day = obj.day;
		month = obj.month;
		year = obj.year;
	}
};

class Lot {
protected:
	Date date;
	double price;
	int cant;

public:
	Lot() { }
	Lot(const Date &obj, const int c, const double pr = 1) : date(obj), cant(c), price(pr) { }
	Lot(const int d, const int m, const int y, const int c, const double pr = 1) : date(d, m, y), cant(c), price(pr) { }
	Lot(const Lot &obj) { *this = obj; }
	~Lot() { }
	Lot& operator=(const Lot &obj) {
		date = obj.date;
		price = obj.price;
		cant = obj.cant;
	}
	friend istream& operator>>(istream &in, Lot &obj) {
		in >> obj.date.day >> obj.day.month >> obj.day.year >> obj.cant >> obj.price;
	}
};

class LotPerisabil : virtual public Lot {
protected:
	int availableFor;

public:
	LotPerisabil() { }
	LotPerisabil(const Date &obj, const int c, const double pr = 1, const int av = 7) : Lot(obj, c, pr), availableFor(av) { }
	LotPerisabil(const int d, const int m, const int y, const int c, const double pr = 1, const int av = 7) : Lot(d, m, y, c, pr), availableFor(av) { }
	LotPerisabil(const LotPerisabil &obj) { *this = obj; }
	~LotPerisabil() { }
	LotPerisabil& operator=(const LotPerisabil &obj) {
		date = obj.date;
		price = obj.price;
		cant = obj.cant;
		availableFor = obj.availableFor;
	}
	friend istream& operator>>(istream &in, LotPerisabil &obj) {
		in >> obj.date.day >> obj.day.month >> obj.day.year >> obj.cant >> obj.price >> obj.availableFor;
	}
};

class LotPromotie : virtual public Lot {
protected:
	double discount;

public:
	LotPromotie() { }
	LotPromotie(const Date &obj, const int c, const double pr = 1,const double disc = 0) : Lot(obj, c, pr), discount(disc) { }
	LotPromotie(const int d, const int m, const int y, const int c, const double pr = 1,const double disc = 0) : Lot(d, m, y, c, pr), discount(disc) { }
	LotPromotie(const LotPromotie &obj) { *this = obj; }
	~LotPromotie() { }
	LotPromotie& operator=(const LotPromotie &obj) {
		date = obj.date;
		price = obj.price;
		cant = obj.cant;
		discount = obj.discount;
	}
	friend istream& operator>>(istream &in, LotPromotie &obj) {
		in >> obj.date.day >> obj.day.month >> obj.day.year >> obj.cant >> obj.price >> obj.discount;
	}
};

class LotPerProm : public LotPromotie, public LotPerisabil {
public:
	LotPerProm() { }
	LotPerProm(const Date &obj, const int c, const double pr = 1, const int av = 7, const double disc = 0) : Lot(obj, c, pr) { 
		availableFor = av;
		discount = disc;
	}
	LotPerProm(const int d, const int m, const int y, const int c, const double pr = 1, const int av = 7, const double disc = 0) : 
		Lot(d, m, y, c, pr) {
			availableFor = av;
			discount = disc;
		}
	LotPerProm(const LotPerProm &obj) { *this = obj; }
	~LotPerProm() { }
	LotPerProm& operator=(const LotPerProm &obj) {
		date = obj.date;
		price = obj.price;
		cant = obj.cant;
		availableFor = obj.availableFor;
		discount = obj.discount;
	}
	friend istream& operator>>(istream &in, LotPerProm &obj) {
		in >> obj.date.day >> obj.day.month >> obj.day.year >> obj.cant >> obj.price >> obj.availableFor >> obj.discount;
	}
};

class Produs {
private:
	string name;
	string um;
	vector<Lot*> lots;


};

int main() {

	return 0;
}