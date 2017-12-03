#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> vec;
vector<int> bucket;

int main() {
    int n, bsize, minim = 99999, m, i;

    cin >> n >> m;
    bsize = (int)sqrt(n);
    for (i = 0; i < n; ++i) {
        if (i % bsize == 0 && i) {
            bucket.push_back(minim);
            minim = 99999;
        }
        int x;
        cin >> x;
        minim = min(x, minim);
        vec.push_back(x);
    }
    if (i % bsize == 0) {
        bucket.push_back(minim);
    }

    int st, dr;
    for (int i = 0; i < m; ++i) {
        cin >> st >> dr;
        minim = 99999;
        while (st % bsize && st <= dr) {
            minim = min(minim, vec[st]);
            ++st;
        }
        while ((dr - st) / (bsize - 1)) {
            minim = min(minim, bucket[st / bsize]);
            st += bsize;
        }
        while (st <= dr) {
            minim = min(minim, vec[st]);
            ++st;
        }
        cout << minim << '\n';
    }

    return 0;
}
