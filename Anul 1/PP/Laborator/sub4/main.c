#include <stdio.h>
#include <stdlib.h>

int cmp(const void *x, const void *y) {
    if (*((char*)x) == *((char*)y)) {
        return 1;
    }
    return 0;
}

void* cautare(const void *x, const void *t, int n, int d, int (*cmpValori)(const void *, const void *)) {
    char *p = (char*)t;
    int i;

    for (i = 0; i < n; ++i) {
        if (cmpValori(x, p + i * d)) {
            return (void*)(p + i * d);
        }
    }

    return NULL;
}

int main()
{
    char t[] = {1, 2, 3, 4, 5, 6, 7, 5};
    char x = 0;

    char *s;
    s = (char*)cautare(&x, t, 8, 1, cmp);

    while (s != NULL) {
        printf("%d ", (s - t) / sizeof(char));
        *s = -x;
        s = (char*)cautare(&x, t, 8, 1, cmp);
    }

    return 0;
}
