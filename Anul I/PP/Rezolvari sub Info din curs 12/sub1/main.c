#include <stdio.h>
#include <stdlib.h>

double *read(int *n) {
    double *p;
    printf("Introduceti numarul de elemente: ");
    scanf("%d", n);
    p = (double*)malloc(*n * sizeof(double));

    int i;
    for (i = 0; i < *n; ++i) {
        printf("Introduceti elementul %d: ", i + 1);
        scanf("%lf", &p[i]);
    }

    return p;
}

void print(int n, double *p) {
    int i;
    printf("Elementele vectorului: ");
    for (i = 0; i < n; ++i) {
        printf("%lf ", p[i]);
    }
}

int minim(int n, double *p, int st, int dr) {
    int min_val = p[st], poz = st, i;

    for (i = st; i < dr; ++i) {
        if (p[i] < min_val) {
            min_val = p[i];
            poz = i;
        }
    }

    return poz;
}

int main()
{
    int n;
    double *p = read(&n);
    int i, min_poz;
    for (i = 0; i < n; ++i) {
        min_poz = minim(n, p, i, n);
        int aux = p[i];
        p[i] = p[min_poz];
        p[min_poz] = aux;
    }
    print(n, p);

    return 0;
}
