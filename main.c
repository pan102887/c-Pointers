#include "chapt_7_practice.h"
#include "chapt_8_demo.h"
#include "chapt_8_practice.h"
#include "linked_list.h"
#include "eight_queens.h"
#include "global.h"

#include <stdio.h>



#ifdef _TEST_
void test() {
    chapt_7_run();
    chapt_8_demo_run();
    chapt_8_practice_run();
    eight_queens_test();
}
#endif

int main(int argc, char **argv)
{

#ifdef _TEST_
    test();
#endif
    return 0;
}
