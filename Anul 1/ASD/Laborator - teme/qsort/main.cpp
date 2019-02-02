#include <fstream>
#include <vector>
using namespace std;

void qsort(vector<int> &p, int lo, int hi) {
    int i = lo, j = hi, pivot = p[(lo + hi) / 2];

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
    if (lo < j) {
        qsort (p, lo, j);
    }
    if (i < hi) {
        qsort (p, i, hi);
    }
}

int main() {
    int n;
    vector<int> vec;

    ifstream in("algsort.in");
    in >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;
        vec.push_back(x);
    }
    in.close();

    qsort(vec, 0, n - 1);

    ofstream out("algsort.out");
    for (int i = 0; i < n; ++i) {
        out << vec[i] << ' ';
    }
    out.close();

    return 0;
}
