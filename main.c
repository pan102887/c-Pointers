#include "my_average.h"
#include "chapt_7_practice.h"
#include "chapt_8_demo.h"
#include "chapt_8_practice.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    double a = average(5, 2, 3, 4, 5, 8);
    printf("average: %lf\n", a);
    chapt_7_run();
    chapt_8_demo_run();
    chapt_8_practice_run();

    return 0;
}
