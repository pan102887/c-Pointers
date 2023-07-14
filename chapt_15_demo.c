#include "chapt_15_demo.h"
#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void perror_test(void)
{
    #if 0
    for(;;) {
        printf("errno: %d\n", errno);
        perror("perror test");
    
        if (errno == 133) {
            break;
        }
        errno++;
    }
    errno = 0;
    #endif
}

void std_out_test(void)
{
    printf("print something or other\n");
    // fflush 的作用是强制将缓冲区内的数据立即写入
    fflush(stdout);
    #if defined(FOPEN_MAX)
        printf("FOPEN_MAX: %d\n", FOPEN_MAX);
    #endif
    #ifdef FILENAME_MAX
        printf("FILENAME_MAX: %d\n", FILENAME_MAX);
    #endif
}

#ifdef _TEST_
void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    perror_test();
    std_out_test();
    print_dividing_line("");
}
#endif