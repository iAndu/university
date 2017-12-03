#include <iostream>

using namespace std;

long long xp(int n, int exp) {
    if (exp == 1) {
        return n;
    }
    if (exp % 2) {
        return n * xp(n, exp - 1);
    }
    return xp(n, exp >> 1) * xp(n, exp >> 1);
}

int main() {
    int n, exp;

    cin >> n >> exp;
    cout << xp(n, exp);
    return 0;
}
