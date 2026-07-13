#include <stdio.h>

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    char v = 0x81;
    printf("%d\n", v);
    printf("%ld\n", sizeof(int));
    return 0;
}
