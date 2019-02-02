#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class Stack {
	T v[1000];
	int size = 0;
public:
	bool push(T el);
	bool pop();
	 friend istream& operator>>(istream &in, Stack<T> &x); {
 };

template<class T>
bool Stack<T>::push(T el) {
	if (size < 1000) {
		v[size++] = el;
		return 1;
	}
	return 0;
}

template<class T>
bool Stack<T>::pop() {
	if (size > 0) {
		--size;
		return 1;
	}
	return 0;
}

template<>
istream& operator>>(istream &stream, Stack<char*> &st) {
	int size;
	stream >> size;
	char buffer[1000];
	for (int i = 1; i <= size; ++i) {
		stream >> buffer;
		st.push(buffer);
	}
	return stream;
}

template<>
bool Stack<char*>::push(char *el) {
	if (size < 1000) {
		v[size++] = new char[strlen(el) + 1];
		strcpy(v[size - 1], el);
		return 1;
	}
	return 0;
}
 
int main() {
	return 0;
}