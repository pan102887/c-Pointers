#include "test.h"

#include <stdio.h>



int main(int argc, char **argv)
{
#ifdef _TEST_
    test_run(argc, argv);
#else
    char v = 0x81;
    printf("%d\n", v);
    printf("%ld\n", sizeof(int));
#endif
    return 0;
}
