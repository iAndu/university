#include <unistd.h>

int main() 
{
    if (write(1, "Hello World!\n", 14) != 14) 
    {
        write(2, "There was an error at printing HW!\n", 36);
        return -1;
    }

    return 0;

}
