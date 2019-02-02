#include <fstream>
#include <vector>
#define NMAX (500000 << 2) + 1
using namespace std;

vector<int> vec;
int *ivl[NMAX];

int *sorted(int *a, int *b, int nra, int nrb) {
    vector<int> c;
    int conta = 0, contb = 0;

    while (conta < nra && contb < nrb) {
        if (*(a + conta) <= *(b + contb)) {
            c.push_back(*(a + conta++));
        } else {
            c.push_back(*(b + contb++));
        }
    }
    while (conta < nra) {
        c.push_back(*(a + conta++));
    }
    while (contb < nrb) {
        c.push_back(*(b + contb++));
    }

    conta = 0;
    while (conta < nra + nrb) {
        *(a + conta) = c[conta++];
    }

    return a;
}

void create_arbint(int nod, int st, int dr) {
    if (st == dr) {
        ivl[nod] = &vec[st];
    } else {
        int mij = st + ((dr - st) >> 1);
        create_arbint(nod << 1, st, mij);
        create_arbint((nod << 1) + 1, mij + 1, dr);
        ivl[nod] = sorted(ivl[nod << 1], ivl[(nod << 1) + 1], mij - st + 1, dr - mij);
    }
}

int main() {
    int n;

    ifstream in("algsort.in");
    in >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        vec.push_back(x);
    }
    in.close();

    create_arbint(1, 0, n - 1);

    ofstream out("algsort.out");
    for (int i = 0; i < n; ++i) {
        out << vec[i] << ' ';
    }
    out.close();

    return 0;
}
