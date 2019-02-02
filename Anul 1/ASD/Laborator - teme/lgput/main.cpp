#include <cstdio>

using namespace std;

long long power(long long nr, long long pow) {
	if (pow == 1) {
		return nr;
	} else if (pow % 2) {
		return (nr * power(nr, pow - 1)) % 1999999973;
	} else {
		long long aux = power(nr, pow >> 1) % 1999999973;
		return (aux * aux) % 1999999973;
	}
}

int main() {
	long long nr, pow;

	FILE *input = fopen("lgput.in", "r");
	fscanf(input, "%lld %lld", &nr, &pow);
	fclose(input);

	FILE *output = fopen("lgput.out", "w");
	fprintf(output, "%lld\n", power(nr, pow) % 1999999973);
	fclose(output);

	return 0;
}
