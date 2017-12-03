#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char nume[20];
    int note[3], grupa;
    double medie;
} Student;

double calc_medie(const Student t) {
    int i, sum = 0;

    for (i = 0; i < 3; ++i) {
        sum += t.note[i];
    }

    return (double)sum / 3;
}

int cmp(const void *a, const void *b) {
    if (((Student*)a)->medie == ((Student*)b)->medie) {
        return strcmp(((Student*)a)->nume, ((Student*)b)->nume);
    }
    return  ((Student*)b)->medie - ((Student*)a)->medie;
}

void print (Student *t, int n, int g) {
    FILE *out = fopen("grupa_g.out", "w");
    int i;

    fprintf(out, "Studentii grupei %d:\n", g);
    for (i = 0; i < n; ++i) {
        if (t[i].grupa == g) {
            fprintf(out, "Nume: %s\n", t[i].nume);
            fprintf(out, "Medie: %lf\n", t[i].medie);
            fprintf(out, "\n");
        }
    }
}

int main()
{
    int n;

    printf("Introduceti numarul de studenti: ");
    scanf("%d", &n);

    Student t[n];
    int i, j;
    for (i = 0; i < n; ++i) {
        printf("Introduceti numele studentului %d: ", i + 1);
        scanf("%s", t[i].nume);
        for (j = 0; j < 3; ++j) {
            printf("Introduceti nota %d a studentului %d: ", j + 1, i + 1);
            scanf("%d", &t[i].note[j]);
        }
        printf("Introduceti grupa studentului %d: ", i + 1);
        scanf("%d", &t[i].grupa);

        t[i].medie = calc_medie(t[i]);
    }

    qsort(t, n, sizeof(Student), cmp);

    print(t, n, 1);

    return 0;
}
