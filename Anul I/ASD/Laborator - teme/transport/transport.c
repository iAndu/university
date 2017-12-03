#include <stdio.h>
#include <stdlib.h>

int sum(int saltele, int *volum) {
	int i, volum_total = 0;

	for (i = 0; i < saltele; ++i) {
		volum_total += volum[i];
	}

	return volum_total;
}

char valid(int val, int saltele, int *volum, int transporturi) {
	int i, save = val;

	for (i = 0; i < saltele && transporturi; ++i) {
		if (volum[i] <= save) {
			save -= volum[i];
		} else {
			save = val;
			--transporturi;
			--i;
		}
	}

	if (i == saltele) {
		return 1;
	}
	return 0;
}

int cautare_binara(int left, int right, int saltele, int *volum, int transporturi) {
	int mid;

	while (left <= right) {
		mid = left + ((right - left) >> 1);
		if (valid(mid, saltele, volum, transporturi)) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	return left;
}

void write(int capacitate) {
	FILE *out = fopen("transport.out", "w");
	fprintf(out, "%d\n", capacitate);
	fclose(out);
}

int main() {
	int saltele, transporturi, *volum, volum_total, capacitate;

	FILE *in = fopen("transport.in", "r");
	fscanf(in, "%d %d", &saltele, &transporturi);

	volum = malloc(saltele * sizeof(int));
	int i;
	for (i = 0; i < saltele; ++i) {
		fscanf(in, "%d", &volum[i]);
	}

	volum_total = sum(saltele, volum);
	capacitate = cautare_binara(1, volum_total, saltele, volum, transporturi);

	write(capacitate);

	return 0;
}
