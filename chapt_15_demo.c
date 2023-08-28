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

void open_file_with_check(FILE **fp, const char *filename, const char *mode)
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
    if (NULL == fp || NULL == *fp) {
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


#ifdef _TEST_
void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    // test();
    read();
    print_dividing_line("");
}
#endif

typedef struct {
    char * name;
    int age;
    char * address;
    char * phone;
    char * email;
} StudentInfo;

int read_random_record(FILE *f, size_t rec_number, StudentInfo * buffer)
{
    fseek(f, rec_number * sizeof(StudentInfo), SEEK_SET);
    return fread(buffer, sizeof(StudentInfo), 1, f);
}