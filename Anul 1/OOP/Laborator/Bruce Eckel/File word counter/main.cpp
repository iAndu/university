#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    string file;

    cout << "Introduceti path-ul fisierului: ";
    cin >> file;
    ifstream in(file);

    string word;
    int counter = 0;
    while (in >> word) {
        ++counter;
    }
    in.close();

    cout << "Numarul de cuvinte din fisier este de " << counter << " cuvinte.";

    return 0;
}
