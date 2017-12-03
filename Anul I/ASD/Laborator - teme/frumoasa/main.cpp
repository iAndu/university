// http://www.infoarena.ro/problema/frumoasa

#include <fstream>
#define NUM 26
#define MOD 1000000007
using namespace std;

void read(long long &n, long long &p) {
    ifstream in("frumoasa.in");
    in >> n >> p;
    in.close();
}

void print (unsigned int card) {
    ofstream out("frumoasa.out");
    out << card << '\n';
    out.close();
}

long long exponate (short num, long long exp) {
    if (exp == 1) {
        return num;
    }
    if (exp % 2) {
        return ((num * exponate(num, exp - 1)) % MOD);
    }
    long long aux = exponate(num, exp >> 1);
    return ((aux * aux) % MOD);
}

int main() {
    long long n, p, card = 1;

    read(n, p);

    if (p >= 26 && n > 26) {
        print(0);
        return 0;
    }

    for (long long i = 0; i < p; ++i) {
        card = (card * (NUM - i)) % MOD;
    }
    if (p != n) {
        card = (card * exponate(NUM - p, n - p)) % MOD;
    }

    print(card);

    return 0;
}
