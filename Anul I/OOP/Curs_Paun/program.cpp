#include<iostream>
using namespace std;

template <class T> class A { };
template<> class A { };
int main() {
A<int> a;
return 0;
}
