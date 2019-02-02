#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    FILE *in = fopen("cuvinte.in", "r"), *out = fopen("cuvinte.out", "w");
    char *cuv = (char*)malloc(256 * sizeof(char));
    char *str = (char*)malloc(256 * sizeof(char));
    char *sep = (char*)malloc(128 * sizeof(char));
    int i, len = 0, n, sw = 0;

    for (i = 1; i < 128; ++i) {
        if (!isalpha((char)i) && i != '-') {
            sep[len++] = (char)i;
        }
    }
    sep[len] = '\0';

    fscanf(in, "%d", &n);
    while (!feof(in)) {
        fscanf(in, "%s", cuv);
        if (!feof(in)) {
            str = strtok(cuv, sep);
            while (str != NULL) {
                if (strlen(str) == n) {
                    fprintf(out, "%s ", str);
                    sw = 1;
                }
                str = strtok(NULL, sep);
            }
        }
    }

    if (!sw) {
        fprintf(out, "Imposibil!\n");
    }

    fclose(in);
    fclose(out);

    return 0;
}
