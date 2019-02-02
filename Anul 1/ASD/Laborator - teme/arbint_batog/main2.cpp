#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> vec, bucket;

void init (int rad) {
    int part = 0, nrBuckets = vec.size() / rad;

    while (part < nrBuckets) {
        int maxim = vec[part * rad], finish = rad * (part + 1);
        for (int i = part * rad + 1; i < finish; ++i) {
            maxim = max(maxim, vec[i]);
        }
        bucket.push_back(maxim);
        ++part;
    }
    if (rad * part != vec.size()) {
        int maxim = vec[part * rad], length = vec.size();
        for (int i = part * rad + 1; i < length; ++i) {
            maxim = max(maxim, vec[i]);
        }
        bucket.push_back(maxim);
    }
}

int maxim_batog (int a, int b, int rad) {
    int maxim = vec[a];

    while (a % rad != 0 && a < b) {
        maxim = max(maxim, vec[a++]);
    }
    while (b - a + 1 >= rad) {
        maxim = max(maxim, bucket[a / rad]);
        a += rad;
    }
    while (a <= b) {
        maxim = max(maxim, vec[a++]);
    }

    return maxim;
}

void update (int part, int rad) {
    int maxim = vec[part * rad], finish = rad * (part + 1);

    for (int i = part * rad; i < finish; ++i) {
        maxim = max(maxim, vec[i]);
    }
    bucket[part] = maxim;
}

int main() {
    int n, m, rad;

    FILE *in = fopen("arbint.in", "r");
    fscanf (in, "%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int x;
        fscanf (in, "%d", &x);
        vec.push_back(x);
    }

    rad = sqrt(n);
    init (rad);

    FILE *out = fopen("arbint.out", "w");
    for (int i = 0; i < m; ++i) {
        int op, a, b;
        fscanf(in, "%d %d %d", &op, &a, &b);
        if (op == 0) {
            fprintf(out, "%d\n", maxim_batog(a - 1, b - 1, rad));
        } else {
            vec[a - 1] = b;
            update((a - 1) / rad, rad);
        }
    }
    fclose(in);
    fclose(out);

    return 0;
}

