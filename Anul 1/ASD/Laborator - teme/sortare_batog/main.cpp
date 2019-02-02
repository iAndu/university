#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

void init (int r, int n, vector<int> &v, vector<int> &b) {
    int part = 0, minim, i;

    while (part < r) {
        int i;
        minim = v[part * r];
        for (i = part * r + 1; i < (part + 1) * r; ++i) {
            minim = min(minim, v[i]);
        }
        b.push_back(minim);
        i = part * r;
        while (v[i] != minim) {
            ++i;
        }
        v[i] = INT_MAX;
        part++;
    }
    minim = v[part * r];
    for (i = part * r + 1; i < n; ++i) {
        minim = min(minim, v[i]);
    }
    b.push_back(minim);
    i = part * r;
    while (v[i] != minim) {
        ++i;
    }
    v[i] = INT_MAX;
}

void update (int r, int part, vector<int> &v, vector<int> &b) {
    int minim, right, i, length = v.size();

    /*if (r * (part + 1) < length && r * (part + 2) > length) {
        right = length;
    } else {
        right = r * (part + 1);
    }*/
    if (part == b.size() - 1) {
        right = v.size();
    } else {
        right = r * (part + 1);
    }
    minim = v[part * r];
    for (i = part * r; i < right; ++i) {
        minim = min(minim, v[i]);
    }
    b[part] = minim;
    i = part * r;
    while (v[i] != minim) {
        ++i;
    }
    v[i] = INT_MAX;
}

int minim_batog (int r, vector<int> &v, vector<int> &b) {
    int minim = b[0], length = b.size(), part = 0;

    for (int i = 1; i < length; ++i) {
        if (b[i] < minim) {
            minim = b[i];
            part = i;
        }
    }

    update(r, part, v, b);

    return minim;
}

int main() {
    int n, r, nr = 0;
    vector<int> v, b;

    FILE *in = fopen("algsort.in", "r");
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        fscanf(in, "%d", &x);
        v.push_back(x);
    }
    fclose(in);
    r = sqrt(n);

    init(r, n, v, b);
    FILE *out = fopen("algsort.out", "w");
    while (nr < n) {
        fprintf (out, "%d ", minim_batog(r, v, b));
        ++nr;
    }
    fprintf(out, "\n");
    fclose(out);

    return 0;
}
