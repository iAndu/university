#include <iostream>

using namespace std;

class O;

void Random(O &param) {
	cout << "LVAL\n";
}

void Random(O &&param) {
	cout << "RVAL\n";
}

class O {
public:
	int *p;
	O(const int _val = 0) {
		cout << "Constructor\n";
		p = new int;
		*p = _val;
	}

	O(const O &other) {
		cout << "Copy constructor\n";
		p = new int;
		*p = *(other.p);
	}

	~O() {
		cout << "Destructor\n";
		if (p != NULL)
			delete p;
	}

	O operator+(const O &other) {
		cout << "Operator +\n";
		O obj;
		*(obj.p) = *(this->p) + *(other.p);
		return obj;
	}

	O(O &&other) {
		cout << "Move constructor\n";
		this->p = other.p;
		other.p = NULL;
		Random(move(other));
	}
};



int main() {
	O b, c;
	O a(move(b+c));

	return 0;
}