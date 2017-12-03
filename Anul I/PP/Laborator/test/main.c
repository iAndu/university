#include <stdio.h>
#include <stdlib.h>

void func () {
    printf("Hello!");
}

int main()
{
    void (*pf)() = func;

    pf();

    return 0;
}
