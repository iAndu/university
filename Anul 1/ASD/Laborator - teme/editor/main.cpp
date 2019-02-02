#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int n, stele, i, j;
    stack<char> stiva;
    string car;
    string sir;

    ifstream in("editor.in");
    ofstream out("editor.out");
    in >> n;
    in.get();
    for (i = 1; i <= n; i++) {
        getline(in, sir);
        stele = 0;
        for (j = sir.size() - 2; j >= 0; j--)
            if (sir[j] == '*')
                stele++;
            else if (stele == 0)
                    car.push_back(sir[j]);
                else stele--;
        //cout << car << '\n';
        for (j = car.size() - 1; j >= 0; j--)
            if (car[j] == '(' || car[j] == '[')
                stiva.push(car[j]);
            else if (!stiva.empty() && ((car[j] == ')' && stiva.top() == '(') || (car[j] == ']' && stiva.top() == '[')))
                    stiva.pop();
                else {
                    out << ":(\n";
                    j = -10;
                }
        if (j == -1) {
            if (stiva.empty())
                out << ":)\n";
            else out << ":(\n";
        }

        car.clear();
        sir.clear();
        stack<char> empty;
        swap (stiva, empty);
    }
    return 0;
}
