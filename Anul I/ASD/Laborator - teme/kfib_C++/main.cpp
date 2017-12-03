#include <fstream>
#include <iostream>
using namespace std;

struct matrice {
    long long mat[2][2];
};

matrice multiply(matrice a, matrice b) {
    matrice aux;

    aux.mat[0][0] = ((a.mat[0][0] * b.mat[0][0]) % 666013 + (a.mat[0][1] * b.mat[1][0]) % 666013) % 666013;
    aux.mat[0][1] = ((a.mat[0][0] * b.mat[0][1]) % 666013 + (a.mat[0][1] * b.mat[1][1]) % 666013) % 666013;
    aux.mat[1][0] = ((a.mat[1][0] * b.mat[0][0]) % 666013 + (a.mat[1][1] * b.mat[1][0]) % 666013) % 666013;
    aux.mat[1][1] = ((a.mat[1][0] * b.mat[0][1]) % 666013 + (a.mat[1][1] * b.mat[1][1]) % 666013) % 666013;

    //cout << aux.mat[0][0] << ' ' << aux.mat[0][1] << '\n' << aux.mat[1][0] << ' ' << aux.mat[1][1] << "\n\n";

    return aux;
}

matrice expi(matrice z, int e) {
    if (e == 1) {
        return z;
    } else if (e % 2) {
        return multiply(z, expi(z, e - 1));
    } else {
        matrice aux = expi(z, e / 2);
        return multiply(aux, aux);
    }
}

int main()
{
    int k;
    matrice z;

    z.mat[0][0] = 0;
    z.mat[0][1] = 1;
    z.mat[1][0] = 1;
    z.mat[1][1] = 1;

    ifstream in("kfib.in");
    in >> k;
    in.close();

    z = expi(z, k - 1);

    ofstream out("kfib.out");
    out << z.mat[1][1] << '\n';
    out.close();

    return 0;
}
