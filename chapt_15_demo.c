#include "chapt_15_demo.h"
#include "global.h"
#include "consumer.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <threads.h>

#define BUFFER_SIZE 5

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

FILE *open_file_with_check(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE *close_file_with_check(FILE *fp)
{
    if (fclose(fp) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    return NULL;
}


void file_read_test(void)
{
    FILE *fp = open_file_with_check("write_test.txt", "wr");
    char *line = alloca(BUFFER_SIZE);
    int count = 0;
    int total_str_len = 0;
    while ((line = fgets(line, BUFFER_SIZE, fp)) != NULL)
    {
        count++;
        total_str_len += strlen(line);
        printf("%s", line);
    }
    printf("count: %d\n", count);
    printf("total_str_len: %d\n", total_str_len);

    close_file_with_check(fp);
}

void gets_test(void)
{
    int count = 0;
    char *line = alloca(BUFFER_SIZE);
    while ((line = fgets(line, BUFFER_SIZE, stdin)) != NULL && line[0] != EOF)
    {
        printf("%s", line);
        count++;
        printf("std read count: %d\n", count);
    }
}

void scanf_test(void)
{
    int count = 0;
    char *line = alloca(BUFFER_SIZE);
    while (scanf("%s", line) != EOF)
    {
        printf("%s\n", line);
        count++;
        printf("std read count: %d\n", count);
        thrd_sleep(&(struct timespec){.tv_sec = 4}, NULL);
    }
}

#ifdef _TEST_
void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    // std_out_test();
    // file_read_test();
    // gets_test();
    scanf_test();
    print_dividing_line("");
}
#endif