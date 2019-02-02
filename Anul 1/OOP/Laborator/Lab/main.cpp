#include <iostream>

using namespace std;

class A {
public:
	int membru;
	void ceva(int param) {
		cout << param << '\n';
	}
};

int main() {
	A obj;
	obj.membru = 3;

	int A::*pMembru = &A::membru;
	cout << obj.*pMembru << endl;

	void (A::*pFunctie)(int) = &A::ceva;
	(obj.*pFunctie)(4);

	return 0;
}