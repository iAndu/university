#include <iostream>
#include <unordered_set>
#include <cstring>
#include <fstream>
#define LMAX 10000005

using namespace std;

struct cuv {
    char s[25];
};

string text, save;
unordered_set<string> my_set;

int main() {
    ifstream in("abc2.in");
    in >> text;
    string str;
    while (in >> str) {
        my_set.insert(str);
    }
    in.close();

    for (unordered_set<string>::iterator it = my_set.begin(); it != my_set.end(); ++it) {
        cout << *it << ' ';
    }

    save = text;
    int nr = 0;
    for (unordered_set<string>::iterator it = my_set.begin(); it != my_set.end(); ++it) {
        size_t poz;
        cout << *it << ' ';
        while ((poz = text.find(*it)) && poz != string::npos) {
            text[poz] = '\0';
            ++nr;
        }
        text = save;
    }

    ofstream out("abc2.out");
    out << nr << '\n';
    out.close();

    return 0;
}
