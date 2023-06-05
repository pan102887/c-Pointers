#include "chapt_7_practice.h"
#include "chapt_8_demo.h"
#include "chapt_8_practice.h"
#include "linked_list.h"
#include "eight_queens.h"
#include "chapt_9_demo.h"
#include "kmp.h"
#include "global.h"

#include <stdio.h>



#ifdef _TEST_
void test() {
    chapt_7_practice_run();
    chapt_8_demo_run();
    chapt_8_practice_run();
    chapt_9_demo_run();
    eight_queens_test();
    kmp_test();
}
#endif

int main(int argc, char **argv)
{

#ifdef _TEST_
    test();
#else
    char v = 0x81;
    printf("%d\n", v);
    printf("%ld\n", sizeof(int));
#endif
    return 0;
}
