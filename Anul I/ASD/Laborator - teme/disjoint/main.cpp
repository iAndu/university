#include <fstream>
#include <vector>
using namespace std;

vector<int> tata, rang;


int cauta(int x) {
    if (tata[x] != x) {
        tata[x] = cauta(tata[x]);
    }
    return tata[x];
}

void reunire(int x, int y) {
    x = cauta(x);
    y = cauta(y);
    if (rang[x] < rang[y]) {
        tata[x] = y;
        rang[y]++;
    } else {
        tata[y] = x;
        rang[x]++;
    }
}

int main() {
    int n, m, x, y, val;

    ifstream in("disjoint.in");
    ofstream out("disjoint.out");
    in >> n >> m;

    for (int i = 0; i <= n; ++i) {
        tata.push_back(i);
        rang.push_back(1);
    }

    for (int i = 0; i < m; ++i) {
        in >> val >> x >> y;
        if (val == 1) {
            reunire(x, y);
        } else {
            if (cauta(x) == cauta(y)) {
                out << "DA\n";
            } else {
                out << "NU\n";
            }
        }
    }
    return 0;
}