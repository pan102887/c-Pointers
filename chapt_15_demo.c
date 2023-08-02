#include "chapt_15_demo.h"
#include "global.h"
#include "consumer.h"

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

void file_write_test(void)
{
    FILE *fp = fopen("write_test.txt", "wr");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    fputc(EOF, fp);
    fputc('\n', fp);
    fputc('\n', fp);
    fclose(fp);

}

void file_flush_test(void)
{
    FILE *fp = fopen("flush_test.txt", "a+");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "This is testing for fprintf...\n");
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
    char c;
    while((c = getc(fp)) != EOF) {
        putchar(c);
    }
    if (fclose(fp) != 0)
    {
        perror("flush_test.txt");
        exit(EXIT_FAILURE);
    }
}

void file_read_test(void)
{
    FILE *fp = fopen("flush_test.txt", "r");
    if (fp == NULL) {
        perror("flush_test.txt");
        exit(EXIT_FAILURE);
    }
    char c;
    while((c = getc(fp)) != EOF) {
        putchar(c);
    }
    if (fclose(fp) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

#ifdef _TEST_
void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    perror_test();
    std_out_test();
    file_write_test();
    file_flush_test();
    file_read_test();
    print_dividing_line("");
}
#endif