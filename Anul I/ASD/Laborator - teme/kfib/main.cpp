#include <cstdio>
#include <cstdlib>

using namespace std;

int initialize(int **z) {
	*z = (int *)malloc(2 * sizeof(int *));
	for (int i = 0; i < 2; ++i) {
		z[i] = (int)malloc(2 * sizeof(int));
	}
}

int ** multiply(int **z, int **y) {
	int first_elem, second_elem, **aux;

	initialize(aux);
	for (int i = 0; i < 2; ++i) {
		first_elem = ((z[i][0] * y[0][i]) % 666013 + (z[i][1] * y[1][i]) % 666013) % 666013;
		second_elem = ((z[i][0] * y[0][i]) % 666013 + (z[i][1] * y[1][i]) % 666013) % 666013;
		aux[i][0] = first_elem;
		aux[i][1] = second_elem;
	}

	return aux;
}

int ** exp(int **z, int k) {
	int **aux;
	initialize(aux);
	if (k == 1) {
		return z;
	} else if (k % 2) {
		return multiply(z, exp(z, k - 1));
	} else {
		aux = exp(z, k / 2);
		return multiply(aux, aux);
	}
}

void print(int val) {
	FILE *out = fopen("kfib.out", "w");
	fprintf(out, "%d\n", val);
	fclose(out);
}

int main() {
	int k, kfib;
	int *fib, **z, *aux;

	FILE *input = fopen("kfib.in", "r");
	fscanf(input, "%d", &k);
	fclose(input);

	*fib = malloc(2 * sizeof(int));
	initialize(z);
	z[0][0] = 0;
	z[0][1] = 1;
	z[1][0] = 1;
	z[1][1] = 1;

	z = exp(z, k);
	kfib = ((fib[0] * z[0][1]) % 666013 + (fib[1] * z[1][1]) % 666013) % 666013;

	print(kfib);
}
