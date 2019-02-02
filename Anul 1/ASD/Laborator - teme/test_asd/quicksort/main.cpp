#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> vec;

void qsort(int st, int dr) {
    if (st != dr) {
    int i = st, j = dr, mij = st + (rand() % (dr - st)), pivot = vec[mij];

    while (i <= j) {
        while (vec[i] < pivot) {
            ++i;
        }
        while (vec[j] > pivot) {
            --j;
        }
        if (i <= j) {
            swap(vec[i], vec[j]);
            ++i;
            --j;
        }
    }

    if (st < j) {
        qsort(st, j);
    }
    if (i < dr) {
        qsort(i, dr);
    }
    }
}

int main() {
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    qsort(0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << vec[i] << ' ';
    }

    return 0;
}
