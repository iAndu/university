#include <fstream>
#include <vector>
#include <cmath>
#define NMAX 100001
using namespace std;

vector<int> vec;
int maxim[(NMAX << 2) + 1];

void construct_max(int nod, int st, int dr) {
    if (st == dr) {
        maxim[nod] = vec[st];
    } else {
        int mij = st + ((dr - st) >> 1);
        construct_max(nod << 1, st, mij);
        construct_max((nod << 1) + 1, mij + 1, dr);
        maxim[nod] = max(maxim[nod << 1], maxim[(nod << 1) + 1]);
    }
}

int raspuns(int nod, int st, int dr, int x, int y) {
    if (x <= st && dr <= y) {
        return maxim[nod];
    }
    int mij = st + ((dr - st) >> 1);
    if (y <= mij) {
        return raspuns(nod << 1, st, mij, x, y);
    }
    if (x > mij) {
        return raspuns((nod << 1) + 1, mij + 1, dr, x, y);
    }
    return max(raspuns(nod << 1, st, mij, x, y), raspuns((nod << 1) + 1, mij + 1, dr, x, y));
}

void actualizare(int nod, int st, int dr, int x) {
    if (st == dr) {
        maxim[nod] = vec[x];
    } else {
        int mij = st + ((dr - st) >> 1);
        if (x <= mij) {
            actualizare(nod << 1, st, mij, x);
        } else {
            actualizare((nod << 1) + 1, mij + 1, dr, x);
        }
        maxim[nod] = max(maxim[nod << 1], maxim[(nod << 1) + 1]);
    }
}

int main() {
    int n, m, op, x, y;
    ifstream in("arbint.in");
    in >> n >> m;
    vec.push_back(0);
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        vec.push_back(x);
    }

    construct_max(1, 1, n);

    ofstream out("arbint.out");
    for (int i = 0; i < m; ++i) {
        in >> op >> x >> y;
        if (op == 0) {
            out << raspuns(1, 1, n, x, y) << '\n';
        } else {
            vec[x] = y;
            actualizare(1, 1, n, x);
        }
    }
    in.close();
    out.close();

    return 0;
}
