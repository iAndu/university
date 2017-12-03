// Programul formeaza cel mai mare si cel mai mic numar din cifrele unui numar dat

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nr, save, cif = 9, count, maxNr = 0, minNr = 0, i, j;

    scanf("%d", &nr);
    save = nr;

    // Formarea celui mai mare numar
    i = 9;
    while (i >= 0 && nr != 0) {
        count = 0;
        while (nr != 0) {
            if (nr % 10 == i) {
                count++;
            }
            nr /= 10;
        }
        j = 1;
        while (j <= count) {
            maxNr = maxNr * 10 + i;
            j++;
        }
        i--;
        nr = save;
    }
    printf("Cel mai mare numar format: %d\n", maxNr);

    // Cel mai mic numar
    while (nr != 0) { // Cauta cea mai mica cifra diferita de 0 pentru initializarea numarului
        if (nr % 10 < cif && nr % 10 != 0) {
            cif = nr % 10;
        }
        nr /= 10;
    }
    if (save != 0) { // Daca numarul este nul, minNr ramane 0
        minNr = cif;
    }
    i = 0;
    nr = save;
    while (i <= 9 && nr != 0) {
        count = 0;
        while (nr != 0) {
            if (nr % 10 == i) {
                count++;
            }
            nr /= 10;
        }
        j = 1;
        if (i == cif) // Daca cifra selectata este prima gasita in primul pas, retinem ca am folosit deja una din ele
            count--;
        while (j <= count) {
            minNr = minNr * 10 + i;
            j++;
        }
        i++;
        nr = save;
    }
    printf("Cel mai mic numar format: %d\n", minNr);
    scanf("%d", &i); // Retinerea afisarii

    return 0;
}
