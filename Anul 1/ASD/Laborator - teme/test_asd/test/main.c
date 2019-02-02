#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

int compar(const void *x, const void *y, int d) {
    return memcmp(x, y, d);
}

void sortare(const void *a, int n, int d, int (*cmp)(const void *, const void *, int)) {
    int i, j;
    for (i = 0; i < n - 1; ++i) {
        char *x = a + i * d;
        for (j = i + 1; j < n; ++j) {
            char *y = a + j * d;
            if (cmp(x, y, d)) {
                void *aux = malloc(d);
                memcpy(aux, x, d);
                memcpy(x, y, d);
                memcpy(y, aux, d);
            }
        }
    }
}

int main()
{
    double a[5];
    a[0] = 5, a[1] = 4, a[2] = 3, a[3] = 2, a[4] = 1;

    sortare(a, 5, sizeof(double), compar);

    return 0;
}
