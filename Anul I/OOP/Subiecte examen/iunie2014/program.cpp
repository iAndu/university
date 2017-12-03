#include <iostream>
using namespace std;

class A {
public: void f() { }
};

class B : protected A { };

int main() {
B obj;
A *ptr = &obj;

return 0;
}
