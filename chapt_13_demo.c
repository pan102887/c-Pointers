#include "chapt_13_demo.h"
#include "global.h"

#include <stdio.h>

// T -> R
#define FUNC(T,R,PN) R (*PN)(T)

int f_1(void) {
    return 1;
}

int f_2(void) {
    return 2;
}

int add_one(int num) {
    return num + 1;
}

void chapt_13_demo_run(void)
{
    print_dividing_line("chapt_13_demo_run");
    int (*f[2])();
    f[0] = f_1;
    f[1] = f_2;

    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", f[i]());
    }

    int (*abc)[2];
    int a[2] = {1, 2};
    abc = &a;
    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", (*abc)[i]);
    }

    // c is a pointer to a function that returns a pointer to a pointer to a function that returns an int
    int (**(*c)())();
    // d is pointer to array 10 of pointer to function (int, double) returning pointer to pointer to function returning pointer to function returning pointer to int
    int *(*(*(*(*(*d)[10])(int, double)))())();

    (*(void(*)())0); // cast 0 to a pointer to a function that returns void
    // (*(void(*)())0)(); // call the function that returns void    
    FUNC(int, int, p);
    p = add_one;
    printf("%d\n", p(4));
    



    print_dividing_line("");

}