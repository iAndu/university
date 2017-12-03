#include <fstream>
#include <string>
#include <stack>

using namespace std;

struct stiv {char sym; int poz;};

int main()
{
    int v[100000], m, y;
    string sir;
    stack<stiv> stiva;
    stiv x;

    ifstream in("parantezare.in");
    ofstream out("parantezare.out");

    getline(in, sir);
    for (int i = 0; i < sir.size(); i++) {
        if (sir[i] == '(') {
            x.sym = sir[i];
            x.poz = i;
            stiva.push(x);
        }
        else if (sir[i] == ')') {
            x = stiva.top();
            stiva.pop();
            v[x.poz] = i;
            v[i] = x.poz;
        }
    }
    in >> m;
    for (int i = 1; i <= m; i++) {
        in >> y;
        out << v[y] << ' ';
    }
    in.close();
    out.close();

    return 0;
}
