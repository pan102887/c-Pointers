#include "chapt_15_demo.h"
#include "global.h"
#include "consumer.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <threads.h>
#include <pthread.h>

#define BUFFER_SIZE 128

static inline void open_file_with_check(FILE **fp, const char *filename, const char *mode)
{
    *fp = fopen(filename, mode);
    if (*fp == NULL)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
}

void close_file_with_check(FILE **fp)
{
    if (NULL == fp || NULL == *fp)
    {
        return;
    }
    if (fclose(*fp) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    *fp = NULL;
}

void test(void)
{
    FILE *fp;
    open_file_with_check(&fp, "test.txt", "r+");
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    size_t line = 0;
    for (;;)
    {
        fprintf(fp, "current line is %ld\n", ++line);
        fflush(fp);
        thrd_sleep(&(struct timespec){.tv_sec = 1}, NULL);
        if (line >= 6)
        {
            break;
        }
    }
    close_file_with_check(&fp);
}
void read(void)
{
    FILE *fp;
    open_file_with_check(&fp, "test.txt", "r");

    // char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    // while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    // {
    //     printf("%s", buffer);
    // }

    char c;
    size_t count = 0;
    int skip = 1;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '0' && skip != 0)
        {
            ungetc(c, fp);
            fseek(fp, 1, SEEK_CUR);
            skip = 0;
            // continue;
        }
        printf("%c", c);
        fflush(stdout);
        count++;
    }

    printf("\ncount = %ld\n", count);
    close_file_with_check(&fp);
}
static inline void stream_buffer_mode_test(void)
{
    FILE *fp;
    open_file_with_check(&fp, "test.txt", "rw+");
    char *buffer = malloc(BUFSIZ * sizeof(char));
    setvbuf(fp, buffer, _IOLBF, BUFSIZ);



    close_file_with_check(&fp);
}

#include <signal.h>
void signal_print(int sig)
{
    printf("signal %d\n", sig);
    fflush(stdout);
}

#ifdef _TEST_
extern void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    // test();
    read();
    signal(SIGINT, signal_print);
    printf("press ctrl+c to exit\n");
    print_dividing_line("");
}
#endif