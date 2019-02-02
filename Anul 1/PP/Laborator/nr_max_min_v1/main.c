/* Program ce formeaza cel mai mare, respectiv cel mai mic numar folosind cifrele unui numar. _V1_ */

#include <stdio.h>
#include <stdlib.h>

int max, min;

struct Number { // Structura - cif retine cifra, iar poz pozitia acesteia in numar (incepand cu unitatile)
    int cif, poz;
};

struct Number cifraMaxima(int nr) {
    int i = 1;
    struct Number maxC;

    maxC.cif = 0;
    while (nr != 0) {
            if (nr % 10 > maxC.cif) {
                maxC.cif = nr % 10;
                maxC.poz = i;
            }
            i++;
            nr /= 10;
        }
    return maxC;
}

struct Number cifraMinima(int nr) {
    int i = 1;
    struct Number minC;

    minC.cif = 9;
    minC.poz = 1;
    while (nr != 0) {
            if (nr % 10 < minC.cif) {
                if ((nr % 10 == 0 && min != 0) || nr % 10 != 0) {
                    minC.cif = nr % 10;
                    minC.poz = i;
                }
            }
            i++;
            nr /= 10;
        }
    return minC;
}

int pow(int poz) { // Ridica 10 la puterea *poz*
    int a, i;

    a = 10;
    for (i = 1; i < poz; i++)
        a = a * 10;
    return a;
}

int count(nr) {
    int c = 0;

    while (nr != 0) {
        c++;
        nr /= 10;
    }

    return c;
}

int main()
{
    int nr, aux, i, a, b, nrCifre, auxCif;
    struct Number maxC, minC;

    scanf("%d", &nr);
    if (nr < 0) {
        printf("Numarul trebuie sa fie natural, pozitiv!\n");
        scanf("%d", &a);
        return 0;
    }

    aux = nr;
    auxCif = nrCifre = count(nr);

    while (nrCifre != 0) {
        maxC = cifraMaxima(nr);
        max = max * 10 + maxC.cif;
        a = pow(maxC.poz);
        b = a / 10;
        nr = nr / a * b + nr % b; // Eliminam cifra selectata
        nrCifre--;
    }

    while (auxCif != 0) {
        minC = cifraMinima(aux);
        min = min * 10 + minC.cif;
        a = pow(minC.poz);
        b = a / 10;
        aux = aux / a * b + aux % b; //Eliminam cifra selectata
        auxCif--;
        //Daca in numar raman doar 0-uri, ciclarea se opreste, altfel pune valori de 9 in locul acestora
        if (aux == 0)
            auxCif = 0;
    }

    printf("Numarul maxim este: %d\nNumarul minim este: %d\n", max, min);
    scanf("%d", &a);

    return 0;
}
