#include <stdio.h>
#include <stdlib.h>

int **matrix(int n) {
    int **p;

    p = (int**)calloc(n, sizeof(int*));
    int i;
    for (i = 0; i < n; ++i) {
        p[i] = (int*)calloc(n, sizeof(int));
    }
    int j;
    for (i = 1; i < n; ++i) {
        for (j = i; j < n; ++j) {
            p[i][j] = p[j][i] = i;
        }
    }

    return p;
}

int main() {

    int **p = matrix(5);

    int i, j;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    return 0;
}
