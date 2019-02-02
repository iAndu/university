#include <iostream>
#include <vector>
using namespace std;

vector<int> a, sum;

void read(int &n, int &t) {
    int x;
    cin >> n >> t;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a.push_back(x);
    }
}

void sum_part(int n) {
    sum.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        sum.push_back((sum[i - 1] + a[i]));
    }
}

int bin_search(int st, int dr, int val) {
    int mij;
    while (st <= dr) {
        mij = st + ((dr - st) >> 1);
        if (sum[mij] == val) {
            return mij;
        } else if (sum[mij] < val) {
            st = mij + 1;
        } else dr = mij - 1;
    }

    return st;
}

int main() {
    int n, t, poz, st = 0, dr, mij, maxx = 0;

    read(n, t);
    sum_part(n);

    dr = n - 1;
    while (st <= dr) {
        mij = st + ((dr - st) >> 1);
        if (sum[mij] == t) {
            dr = mij;
            st = n + 1;
        } else if (sum[mij] < t) {
            st = mij + 1;
        } else dr = mij - 1;
    }

    maxx = dr + 1;
    st = 0;
    for (int i = dr + 1; i < n; ++i) {
        poz = bin_search(st, i, sum[i] - t);
        if (i - poz > maxx) {
            maxx = i - poz;
        }
        st = poz;
    }

    cout << maxx << '\n';

    return 0;
}
