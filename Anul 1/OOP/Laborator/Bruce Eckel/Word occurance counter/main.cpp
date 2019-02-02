#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    string file, word;

    cout << "Include file's path: ";
    cin >> file;
    cout << "Include word looking for: ";
    cin >> word;

    ifstream in(file);
    string str;
    int counter = 0;
    while (in >> str) {
        if (str == word) {
            ++counter;
        }
    }
    in.close();

    cout << "Word " << word << " occures " << counter << " times in the file.";

    return 0;
}
