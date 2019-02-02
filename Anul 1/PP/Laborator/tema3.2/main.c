#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void show_menu() {
    printf("Optiuni:\n");
    printf("--------\n");
    printf("1. Numarul de aparitii al unui cuvant\n");
    printf("2. Cuvintele care nu contin consoane\n");
    printf("3. Suma numerelor din fisier\n");
    printf("4. Cuvintele palindromice\n");
    printf("5. Terminare program\n\n");
}

void fix_string(char *buffer) {
    int i;
    for (i = 0; i < strlen(buffer); ++i) {
        if (!isalpha(buffer[i]) && !isdigit(buffer[i])) {
            buffer[i] = '\0';
            i = strlen(buffer);
        }
    }
}

void appearance(FILE *in) {
    printf("Introduceti cuvantul: ");
    char *str = malloc(256 * sizeof(char));
    scanf("%s", str);

    char *buffer = malloc(256 * sizeof(char));
    int nr = 0;
    while (!feof(in)) {
        fscanf(in, "%s ", buffer);
        fix_string(buffer);
        if (!strcmp(str, buffer)) {
            ++nr;
        }
    }

    printf("Numarul de aparitii al cuvantului \"%s\" este: %d\n\n", str, nr);
    fseek(in, 0, SEEK_SET);
}

short not_vowel(char x) {
    if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u') {
        return 0;
    }
    return 1;
}

void no_cons(FILE *in) {
    char *buffer = malloc(256 * sizeof(char));

    printf("Cuvintele ce nu contin consoane sunt: ");
    while (!feof(in)) {
        fscanf(in, "%s ", buffer);
        fix_string(buffer);
        int i, len = strlen(buffer);
        for (i = 0; i < len; ++i) {
            if (not_vowel(buffer[i])) {
                i = len + 1;
            }
        }
        if (i == len && len) {
            printf("%s ", buffer);
        }
    }
    printf("\n\n");
    fseek(in, 0, SEEK_SET);
}

void nr_sum(FILE *in) {
    long long sum = 0;
    char *buffer = malloc(256 * sizeof(char));

    while (!feof(in)) {
        fscanf(in, "%s ", buffer);
        fix_string(buffer);
        sum += atoi(buffer);
    }

    printf("Suma numerelor din fisier este: %I64d\n\n", sum);
    fseek(in, 0, SEEK_SET);
}

void palindroms(FILE *in) {
    char *buffer = malloc(256 * sizeof(char));

    printf("Cuvintele palindrom sunt: ");
    while (!feof(in)) {
        fscanf(in, "%s ", buffer);
        fix_string(buffer);
        int i, len = strlen(buffer);
        for (i = 0; i < len >> 1; ++i) {
            if (buffer[i] != buffer[len - i - 1] || isdigit(buffer[i])
                || !isalpha(buffer[i])) {
                i = len;
            }
        }
        if (i == len >> 1 && len) {
            printf("%s ", buffer);
        }
    }
    printf("\n\n");
    fseek(in, 0, SEEK_SET);
}

int main() {
    show_menu();

    char op;
    FILE *in = fopen("data.in", "r");
    scanf("%c", &op);
    while (op - '0' != 5) {
        scanf("%*c");
        switch (op) {
            case '1': appearance(in);
                    break;
            case '2': no_cons(in);
                    break;
            case '3': nr_sum(in);
                    break;
            case '4': palindroms(in);
                    break;
            default: printf("Optiune invalida!\n\n");
                    break;
        }
        scanf("%c", &op);
    }
    fclose(in);

    return 0;
}
