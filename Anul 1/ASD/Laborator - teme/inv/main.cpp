#include <cstdio>
#include <vector>
#define NMAX 500000
using namespace std;

int n, b[NMAX], counter;
vector<int> a;

void mergeSort(int left, int right) {
    int i, j, k, mid = left + ((right - left) >> 1), multiply = 0, val;

    if (left == right)
        return;

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    i = k = left;
    j = mid + 1;
    val = a[j];
    while (i <= mid || j <= right) {
        if (j > right || (i <= mid && a[i] <= a[j])) {
            if (a[i] != val) {
                counter = (counter + multiply) % 9917;
            }
            b[k++] = a[i++];
        }
        else {
            multiply++;
            b[k++] = a[j++];
        }
    }
    if (left != 0 || right != (n - 1)) {
        for (k = left; k <= right; k++) {
            a[k] = b[k];
        }
    }
}

int main() {
    int i, x;

    FILE *in = fopen("inv.in", "r");
    fscanf(in, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(in, "%d", &x);
        a.push_back(x);
    }
    fclose(in);

    mergeSort(0, n - 1);

    FILE *out = fopen("inv.out", "w");
    fprintf(out, "%d ", counter);
    fclose(out);

    return 0;
}
