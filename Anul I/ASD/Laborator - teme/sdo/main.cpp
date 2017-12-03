#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void qsort(vector<int> &p, int lo, int hi, int k) {
    int i = lo, j = hi, mid = (lo + hi) >> 1, pivot = p[mid];

    if (i != j) {
    while (i <= j) {
        while (p[i] < pivot) {
            ++i;
        }
        while (p[j] > pivot) {
            --j;
        }
        if (i <= j) {
            swap(p[i++], p[j--]);
        }
    }
    if (lo < j || i < hi) {
    if (lo <= k && k <= j) {
        qsort (p, lo, j, k);
    } else
    if (k >= i && k <= hi) {
        qsort (p, i, hi, k);
    }
    }
    }
}

int main() {
    int n, k;
    vector<int> vec;

    ifstream in("sdo.in");
    in >> n >> k;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        vec.push_back(x);
    }
    in.close();

    qsort(vec, 0, n - 1, k - 1);

    ofstream out("sdo.out");
    out << vec[k - 1] << '\n';
    out.close();

    return 0;
}
