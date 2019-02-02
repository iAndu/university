#include <fstream>
#include <iostream>
#define SQUARE 3
#define MOD 666013

typedef unsigned long long ull;

using namespace std;

struct matrix {
    ull mat[SQUARE][SQUARE];
};

void read(ifstream &in, ull &x, ull &y, ull &z,
          ull &a, ull &b, ull &c, ull &n) {
    in >> x >> y >> z >> a >> b >> c >> n;
}

void initialize(matrix &var, ull a, ull b, ull c) {
    var.mat[0][0] = var.mat[2][0] = var.mat[0][1] = var.mat[1][1] = 0;
    var.mat[1][0] = var.mat[2][1] = 1;
    var.mat[0][2] = c;
    var.mat[1][2] = b;
    var.mat[2][2] = a;
}

matrix multiply(matrix a, matrix b) {
    matrix aux;

    for (ull i = 0; i < SQUARE; ++i) {
        for (ull j = 0; j < SQUARE; ++j) {
            ull s = 0;
            for (ull k = 0; k < SQUARE; ++k) {
                s = (s + (a.mat[i][k] * b.mat[k][j]) % MOD) % MOD;
            }
            aux.mat[i][j] = s;
        }
    }

    return aux;
}

matrix expi(matrix a, ull exp) {
    if (exp == 1) {
        return a;
    } else if (exp % 2) {
        return multiply(a, expi(a, exp - 1));
    } else {
        matrix aux = expi(a, exp / 2);
        return multiply(aux, aux);
    }
}

ull dayN(matrix var, ull x, ull y, ull z) {
    ull s;

    s = ((x * var.mat[0][2]) % MOD + (y * var.mat[1][2]) % MOD + (z * var.mat[2][2]) % MOD) % MOD;

    return s;
}

int main() {
    matrix var;
    ull t, x, y, z, a, b, c, n, s;

    ifstream in("iepuri.in");
    ofstream out("iepuri.out");
    in >> t;

    for (ull i = 0; i < t; ++i) {
        read(in, x, y, z, a, b, c, n);
        initialize(var, a, b, c);
        var = expi(var, n - 2);
        s = dayN(var, x, y, z);
        out << s << '\n';
    }

    in.close();
    out.close();

    return 0;
}
