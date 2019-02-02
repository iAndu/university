#include <stdio.h>
#include <stdlib.h>

void initialize(int **z) {
	int i;
	for (i = 0; i < 2; ++i) {
		z[i] = malloc(2 * sizeof(int));
	}
}

int ** multiply(int **z, int **y) {
	int first_elem, second_elem, **aux;

    aux = malloc(2 * sizeof(int *));
	initialize(aux);
	int i;
	for (i = 0; i < 2; ++i) {
		first_elem = ((z[i][0] * y[0][i]) % 666013 + (z[i][1] * y[1][i]) % 666013) % 666013;
		second_elem = ((z[i][0] * y[0][i]) % 666013 + (z[i][1] * y[1][i]) % 666013) % 666013;
		aux[i][0] = first_elem;
		aux[i][1] = second_elem;
	}

	return aux;
}

int ** expi(int **z, int k) {
	int **aux;
	aux = malloc(2 * sizeof(int *));
	initialize(aux);
	if (k == 1) {
		return z;
	} else if (k % 2) {
		return multiply(z, expi(z, k - 1));
	} else {
		aux = expi(z, k / 2);
		return multiply(aux, aux);
	}
}

void print(int val) {
	FILE *out = fopen("kfib.out", "w");
	fprintf(out, "%d\n", val);
	fclose(out);
}

int main() {
	int k, kfib, i;
	int *fib, **z;

	FILE *input = fopen("kfib.in", "r");
	fscanf(input, "%d", &k);
	fclose(input);

	fib = malloc(2 * sizeof(int));
    z = malloc(2 * sizeof(int *));
	initialize(z);
	z[0][0] = 0;
	z[0][1] = 1;
	z[1][0] = 1;
	z[1][1] = 1;
    for (i = 0; i < 4; ++i) {
        printf("%d ", z[i % 2][i]);
	}
	printf("\n");
	z = expi(z, k);
	for (i = 0; i < 4; ++i) {
        printf("%d ", z[i % 2][i]);
	}
	printf("\n");
	kfib = ((fib[0] * z[0][1]) % 666013 + (fib[1] * z[1][1]) % 666013) % 666013;

	print(kfib);

	return 0;
}
