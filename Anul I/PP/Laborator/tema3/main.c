#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *in = fopen("date.in", "r");
    FILE *out = fopen("date.out", "w");

    char *str = malloc(256 * sizeof(char));
    fprintf(out, "Cuvintele care contin cratima sunt :\n");
    while (!feof(in)) {
        fscanf(in, "%s ", str);
        if (strchr(str, '-')) {
            fprintf(out, "%s ", str);
        }
    }

    printf("Cuvantul de inlocuit: ");
    char *inl = malloc(256 * sizeof(char));
    scanf("%s", inl);
    printf("Cuvantul cu care sa fie inlocuit: ");
    char *rep = malloc(256 * sizeof(char));
    scanf("%s", rep);

    fprintf(out, "\nFisierul cu cuvantul \"%s\" inlocuit cu \"%s\":\n", inl, rep);
    fseek(in, 0, SEEK_SET);
    while (!feof(in)) {
        fscanf(in, "%s ", str);
        if (!strcmp(str, inl)) {
            fprintf(out, "%s ", rep);
        } else {
            fprintf(out, "%s ", str);
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}
