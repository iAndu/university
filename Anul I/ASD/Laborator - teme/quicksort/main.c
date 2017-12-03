#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, length;
    char sir[60001];

    FILE *in = fopen("r", "editor.in");
    fscanf(in, "%d", &n);
    for (i = 1; i <= n; i++) {
        length = 0;
        while (fscanf(in, "%c", &v[length]) != 'E') {
            length++;
        }
        length--;
    }

    return 0;
}
