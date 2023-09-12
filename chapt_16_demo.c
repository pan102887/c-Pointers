#include "chapt_16_demo.h"

#include <stdlib.h>
#include <stdio.h>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

#ifdef _TEST_
/**
 * ===============================================================
 * ▄▀▀ ▀█▀ █▀▄ █ █▄ █ ▄▀     ▀█▀ ▄▀▄    █▄ █ █ █ █▄ ▄█ ██▄ ██▀ █▀▄ 
 * ▄█▀  █  █▀▄ █ █ ▀█ ▀▄█     █  ▀▄▀    █ ▀█ ▀▄█ █ ▀ █ █▄█ █▄▄ █▀▄
 * =============================================================== 
 */
static inline void atoi_test(void)
{
    printf("the atoi \"123\"'s result is %d\n", atoi("123"));
    printf("the atoi \"-123\"'s result is %d\n", atoi("-123"));
}

static inline void strtol_test(void)
{
    printf("the strtol \"123\"'s result is %ld\n", strtol("123", NULL, 10));
    printf("the strtol \"-123\"'s result is %ld\n", strtol("-123", NULL, 10));
    printf("the strtol \"010\"'s result is %ld\n", strtol("010", NULL, 8));
    char **endptr = malloc(sizeof(char *));
    printf("the strtol \"018\"'s result is %ld\n", strtol("018", endptr, 8));
    printf("%s\n", *endptr);
}
/**
 * ===================== █▄ ▄█ ▄▀▄ ▀█▀ █▄█ =======================
 * ===================== █ ▀ █ █▀█  █  █ █ =======================
 */
#include <math.h>
static inline void sqrt_test(void)
{
    double x = 5.5;
    printf("the sqrt of %lf is %lf\n", x, sqrt(x));
    x = 25.0;
    printf("the sqrt of %lf is %lf\n", x, sqrt(x));
}

static inline void trigonometric_functions_test(void)
{
    double x = 0.0;
    printf("the sin of %lf is %lf\n", x, sin(x));
    printf("the cos of %lf is %lf\n", x, cos(x));
    printf("the tan of %lf is %lf\n", x, tan(x));
    printf("the asin of %lf is %lf\n", x, asin(x));
    printf("the acos of %lf is %lf\n", x, acos(x));
    printf("the atan of %lf is %lf\n", x, atan(x));
    printf("the atan2 of %lf is %lf\n", x, atan2(x, 1.0));
    printf("\n");

    x = PI;
    printf("the sin of %.16lf is %.16lf\n", x, sin(x));
    printf("the cos of %.16lf is %.16lf\n", x, cos(x));
    printf("the tan of %.16lf is %.16lf\n", x, tan(x));
    printf("the atan of %.16lf is %.16lf\n", x, atan(x));
    printf("the atan2 of %.16lf is %.16lf\n", x, atan2(x, 1.0));

    x = 1;
    printf("the asin of %.16lf is %.16lf\n", x, asin(x));
    printf("the acos of %.16lf is %.16lf\n", x, acos(x));

}
/**
 * ======================= ▀█▀ █ █▄ ▄█ ██▀ =====================
 * =======================  █  █ █ ▀ █ █▄▄ =====================
 */
#include <time.h>
static inline void time_test(void)
{
    printf("\n");
    time_t *t = malloc(sizeof(time_t));
    time(t);
    printf("the time is %ld\n", *t);
    printf("the ctime is %s\n", ctime(t));
    
    char time_str[100];
    struct tm *ti;
    ti = gmtime(t);
    strftime(time_str, 100, "%Y-%m-%d %H:%M:%S", ti);
    printf("the formated greenwich time is %s\n", time_str);

    ti = localtime(t);
    strftime(time_str, 100, "%Y-%m-%d %H:%M:%S", ti);
    printf("the formated local time is %s\n", time_str);
}

/**
 * ===  █ █ █ █▄ ▄█ █▀▄    ▄▀▄ █▀▄ ██▀ █▀▄ ▄▀▄ ▀█▀ █ ▄▀▄ █▄ █ ===
 * ===▀▄█ ▀▄█ █ ▀ █ █▀     ▀▄▀ █▀  █▄▄ █▀▄ █▀█  █  █ ▀▄▀ █ ▀█ ===
 */
#include <setjmp.h>
static inline void jump_test(void)
{
    int break_flag = 0;
    jmp_buf jmp;
    int jump_times;
    printf("setjmp return %d\n", (jump_times = setjmp(jmp)));
    for (int i = 0; i < 10; i++)
    {
        printf("the jump_times is %d, and i is %d\n", jump_times, i);
        if (i == 5)
        {
            if ((++break_flag) > 2)
            {
                break;
            }
            longjmp(jmp, jump_times);
        }
    }
}
/**
 * =================== ▄▀▀ █ ▄▀  █▄ █ ▄▀▄ █   ====================
 * =================== ▄█▀ █ ▀▄█ █ ▀█ █▀█ █▄▄ ====================
 */
#include <signal.h>

void (*pre_handler)(int);

static inline void signal_handler(int sig)
{
    printf("ignore the signal %d\n", sig);

    printf("raise the SIGINT\n");

    signal(SIGINT, pre_handler);
    int result = raise(SIGINT);
}
static inline void signal_test(void)
{
    printf("set the ignore of SIGINT\n");
    pre_handler = signal(SIGINT, signal_handler);


    printf("raise the SIGINT\n");
    int result = raise(SIGINT);
}

typedef struct DEMO
{
    char *name;
    int age;
} DEMO;

DEMO *data_list[20];

static void data_list_write(void)
{
    for (int i = 0; i < 20; i++)
    {
        DEMO *demo = malloc(sizeof(DEMO));
        demo->name = malloc(sizeof(char) * 10);
        sprintf(demo->name, "demo%d", i);
        demo->age = i;
        data_list[i] = demo;
    }
}

static void data_list_reader(void)
{
    for (int i = 0; i < 20; i++)
    {
        printf("the demo's name is %s, and age is %d\n", data_list[i]->name, data_list[i]->age);
    }
}

extern void chapt_16_demo_run(void)
{
    // atoi_test();
    // strtol_test();
    // sqrt_test();
    // trigonometric_functions_test();
    // time_test();
    // signal_test();
    // jump_test();

    data_list_write();
    data_list_reader();
}

#endif