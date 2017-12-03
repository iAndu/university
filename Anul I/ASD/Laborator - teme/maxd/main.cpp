/* Programul cauta cel mai mic numar dintr-un interval [a, b] cu proprietatea ca are numar maxim de divizori si afiseaza
de asemenea si cardinalul numerelor ce au numar maxim de divizori din acest interval. */

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

bool check[44723];
vector<int> prim;
int vectorDiv[20001], k = -1;

// Retinerea tuturor factorilor primi posibili ai unui numar
void ciur(int limit){
    int i, j, rad = sqrt(limit), rad2 = sqrt(rad);

    prim.push_back(2);
    for (i = 3; i <= rad2; i += 2){
        if (check[i * i] == 0) {
            for (j = i * i; j <= rad; j = j + i + i) {
                check[j] = 1;
            }
        }
    }
    for (i = 3; i <= rad; i += 2) {
        if (check[i] == 0) {
            prim.push_back(i);
        }
    }
}

// Descompunerae numarului in factori primi
int descomp(int nr) {
    int i = 0, nrDiv = 1, exp, div, n;

    n = prim.size();
    while (nr != 1 && i < n) {
        exp = 0;
        div = prim[i];
        while (nr % div == 0) {
            exp++;
            nr /= div;
        }
        nrDiv *= (exp + 1); // nrDiv = (exp1+1)(exp2+1)...(expn+1)
        i++;
    }
    if (nr != 1) // Exista posibilitatea ca numarul sa fie prim de la sine si sa nu se afle in vector
        nrDiv *= 2;
    vectorDiv[++k] = nrDiv; // Retin numarul de divizori ai fiecarui numar din interval

    return nrDiv;
}

int main() {
    int left, right, i, c = 0, nrCurent, maxDiv = 0, nrComp = 0, nrDiv, minim;

    FILE *in = fopen("maxd.in", "r");
    fscanf(in, "%d %d", &left, &right);
    fclose(in);

    ciur(right);
    for (i = left; i <= right; i++) {
        nrCurent = i;
        nrDiv = descomp(nrCurent);
        if (nrDiv > maxDiv) { // Retinerea minimului si a numarului maxim de divizori
            maxDiv = nrDiv;
            minim = nrCurent;
        }
    }

    for (i = 0; i <= right - left; i++) { // Cautarea tuturor componentelor cu aceasta proprietate
        if (vectorDiv[i] == maxDiv) {
            nrComp++;
        }
    }

    FILE *out = fopen("maxd.out", "w");
    fprintf(out, "%d %d %d", minim, maxDiv, nrComp);
    fclose(out);

    return 0;
}
