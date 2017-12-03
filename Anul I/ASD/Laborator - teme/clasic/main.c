#include <stdio.h>

int main() {
	int noOfArrays, noOfElements;

	FILE *input = fopen("clasic.in", "r");
	FILE *output = fopen("clasic.out", "w");
	fscanf(input, "%d", &noOfArrays);

	int i, j;
	long long xorSum, number;
	for (i = 0; i < noOfArrays; ++i) {
		xorSum = 0;
		fscanf(input, "%d", &noOfElements);
		for (j = 0; j < noOfElements; ++j) {
			fscanf(input, "%lld", &number);
			xorSum ^= number;
		}
		fprintf(output, "%lld\n", xorSum);
	}

	fclose(input);
	fclose(output);

	return 0;
}
