#include <stdio.h>
#include <stdlib.h>

int main() {
    char v[10];
    fgets(v, 10, stdin);
    printf("%s", v);

    return 0;
}
