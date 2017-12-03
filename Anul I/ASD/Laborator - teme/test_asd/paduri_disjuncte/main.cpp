#include <iostream>
#include <vector>
using namespace std;

struct nod {
    int val, rang;
};

vector<nod> vec;

int cauta(int x) {
    while (vec[x].val != x) {
        vec[x].val = cauta(vec[x].val);
    }
    return vec[x].val;
}

void reunire(int x, int y) {
    x = cauta(x);
    y = cauta(y);

    if (vec[x].rang < vec[y].rang) {
        vec[x].val = y;
        vec[y].rang++;
    } else {
        vec[y].val = x;
        vec[x].rang++;
    }
}

int main() {
    int n, m;
    nod v;

    cin >> n >> m;
    v.val = 0;
    v.rang = 1;
    vec.push_back(v);
    for (int i = 1; i <= n; ++i) {
        v.val = i;
        vec.push_back(v);
    }

    for (int i = 0; i < m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            reunire(x, y);
        } else {
            if (cauta(vec[x].val) == cauta(vec[y].val)) {
                cout << "DA\n";
            } else {
                cout << "NU\n";
            }
        }
    }

    return 0;
}
