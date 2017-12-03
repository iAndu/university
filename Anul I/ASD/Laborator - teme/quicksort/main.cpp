#include <cstdio>
#include <vector>
using namespace std;

vector<int> v;

void qsort (int inf, int sup) {
    int i = inf, j = sup, x, aux;
    x = v[i + (j - i) / 2];
    do {
        while (i < sup && v[i] < x) {
            i++;
        }
        while (j > inf && v[j] > x) {
            j--;
        }
        if (i <= j) {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (inf < j) {
        qsort(inf, j);
    }
    if (i < sup) {
        qsort(i, sup);
    }
}

int main() {
    int n, x, i;

    FILE *in = fopen("algsort.in", "r");
    fscanf(in, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(in, "%d", &x);
        v.push_back(x);
    }
    fclose(in);

    qsort(0, n - 1);

    FILE *out = fopen("algsort.out", "w");
    for (i = 0; i < n; i++) {
        fprintf(out, "%d ", v[i]);
    }
    fclose(out);

    return 0;
}
