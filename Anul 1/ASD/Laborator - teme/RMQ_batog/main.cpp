#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void update (int r, vector<int> v, vector<int> &b) {
    int part = 0, minim;

    while (part < r) {
        minim = v[part * r];
        for (int i = part * r + 1; i < (part + 1) * r; ++i) {
            minim = min(minim, v[i]);
        }
        b.push_back(minim);
        part++;
    }
}

int main() {
    int n, m, r;
    vector<int> v, b;

    FILE *in = fopen("rmq.in", "r");
    fscanf(in, "%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf(in, "%d", &x);
        v.push_back(x);
    }

    r = sqrt(n);
    update(r, v, b);
    printf("%d", b[1]);

    FILE *out = fopen("rmq.out", "w");
    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(in, "%d %d", &x, &y);
        --x;
        --y;
        if (x % r == 0 && (y + 1) % r == 0 && (y - x + 1) == r) {
            fprintf(out, "%d\n", b[x / r]);
        } else {
            int minim = v[x];
            while (x % r != 0 && x <= y) {
                minim = min(minim, v[x]);
                ++x;
            }
            while ((y - x + 1) / r > 0) {
                minim = min(minim, b[x / r]);
                x += r;
            }
            while (x <= y) {
                minim = min(minim, v[x]);
                ++x;
            }
            fprintf(out, "%d\n", minim);
        }
    }
    return 0;
}
