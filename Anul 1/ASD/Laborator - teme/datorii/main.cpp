#include <fstream>
#include <vector>
#define NMAX (15000 << 2) + 1
using namespace std;

vector<short> dat;
int arbint[NMAX];

void create_arbint(int nod, int st, int dr) {
    if (st == dr) {
        arbint[nod] = dat[st];
    } else {
        int mij = st + ((dr - st) >> 1);
        create_arbint(nod << 1, st, mij);
        create_arbint((nod << 1) + 1, mij + 1, dr);
        arbint[nod] = arbint[nod << 1] + arbint[(nod << 1) + 1];
    }
}

void update(int nod, int st, int dr, int x) {
    if (st == dr) {
        arbint[nod] = dat[x];
    } else {
        int mij = st + ((dr - st) >> 1);
        if (x <= mij) {
            update(nod << 1, st, mij, x);
        } else {
            update((nod << 1) + 1, mij + 1, dr, x);
        }
        arbint[nod] = arbint[nod << 1] + arbint[(nod << 1) + 1];
    }
}

int querry(int nod, int st, int dr, int x, int y) {
    if (x <= st && dr <= y) {
        return arbint[nod];
    } else {
        int mij = st + ((dr - st) >> 1);
        if (y <= mij) {
            return querry(nod << 1, st, mij, x, y);
        }
        if (mij < x) {
            return querry((nod << 1) + 1, mij + 1, dr, x, y);
        }
        return querry(nod << 1, st, mij, x, y) + querry((nod << 1) + 1, mij + 1, dr, x, y);
    }
}

int main() {
    int n, m;

    ifstream in("datorii.in");
    dat.push_back(0);
    in >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        dat.push_back(x);
    }

    create_arbint(1, 1, n);

    ofstream out("datorii.out");
    for (int i = 0; i < m; ++i) {
        int op, x, y;
        in >> op >> x >> y;
        if (!op) {
            dat[x] -= y;
            update(1, 1, n, x);
        } else {
            out << querry(1, 1, n, x, y) << '\n';
        }
    }
    out.close();

    return 0;
}
