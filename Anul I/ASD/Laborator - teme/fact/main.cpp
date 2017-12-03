#include <cstdio>
#include <climits>
#define LIMIT INT_MAX
using namespace std;

int count_zeros(int number) {
    int div = 5, counter = 0;

    while (number / div != 0) {
        counter += number / div;
        div *= 5;
    }

    return counter;
}

int bin_search(int nr_zero) {
    int left = 1, right = LIMIT, mid, zero_count;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        zero_count = count_zeros(mid);
        if (zero_count == nr_zero) {
            mid = mid - (mid % 5);
            return mid;
        } else if (zero_count < nr_zero) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int nr_zero, answer;

    FILE *in = fopen("fact.in", "r");
    fscanf(in, "%d", &nr_zero);
    fclose(in);

    if (nr_zero == 0) {
        answer = 1;
    } else {
        answer = bin_search(nr_zero);
    }

    FILE *out = fopen("fact.out", "w");
    fprintf(out, "%d\n", answer);
    fclose(out);

    return 0;
}
