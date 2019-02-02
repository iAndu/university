#include <fstream>
#include <cmath>
using namespace std;

long long inversiuni(long long k) {
    double p = (1 + sqrt(1 + 8 * k))/ 2;
    if (p > (long long)p) {
        return (long long)p + 1;
    }
    return (long long)p;
}

int main() {
    long long n;
    long long k;

    ifstream in("farfurii.in");
    in >> n >> k;
    in.close();

    long long p = inversiuni(k);
    long long inv = (p - 1) * ((float)p / 2);
    long long c = inv - k;

    ofstream out("farfurii.out");
    for (long long i = 1; i <= n - p; ++i) {
        out << i << ' ';
    }
    out << n - c << ' ';
    for (long long i = n; i > n - p; --i) {
        if (i != n - c) {
            out << i << ' ';
        }
    }
    out << '\n';
    out.close();

    return 0;
}
