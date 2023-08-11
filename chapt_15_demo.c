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
    if (fclose(*fp) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    *fp = NULL;
}


void file_read_test(void)
{
    FILE *fp;
    open_file_with_check(&fp, "write_test.txt", "wr");
    char *line = alloca(BUFFER_SIZE * sizeof(char));
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

    close_file_with_check(&fp);
}

void gets_test(void)
{
    int count = 0;
    char *line = alloca(BUFFER_SIZE);
    while ((line = fgets(line, BUFFER_SIZE, stdin)) != NULL)
    {
        printf("%s", line);
    }
}

void  scanf_test(void)
{
    FILE *fp;
    open_file_with_check(&fp, "write_test.txt", "wr");


    close_file_with_check(&fp);
}

typedef struct BitWRDemo {
    long a;
    int b;
    int c;
    // char d[10];

} BitWRDemo;


void bit_write_test(void)
{
    FILE *fp;
    size_t size = sizeof(BitWRDemo);
    size_t count = 2;

    BitWRDemo bit_demo_array[2] = {{-1, 0x11111111, 0xffffffff}, {0xF123456789ABCDEF, 0x11111111, __INT32_MAX__}};
    open_file_with_check(&fp, "write_test.txt", "wr");
    size_t total = fwrite(bit_demo_array, size, count, fp);
    printf("total: %ld\n", total);
    close_file_with_check(&fp);

    BitWRDemo bit_demo_array2[2];
    open_file_with_check(&fp, "write_test.txt", "r");
    total = fread(bit_demo_array2, size, count, fp);
    close_file_with_check(&fp);

    for (size_t i = 0; i < count; i++) {
        printf("a: %16lX \tb: %8X \tc: %8X\n", bit_demo_array2[i].a, bit_demo_array2[i].b, bit_demo_array2[i].c);
    }
}

void random_write_test(void)
{
    FILE *fp;
    open_file_with_check(&fp, "test.txt", "r");
    char *buff = malloc(sizeof(char) * BUFFER_SIZE);
    size_t count = 0;
    // while (fscanf(fp, "%[^\n]", buff) != EOF) {
    //     printf("%s\tcount: %ld\n", buff, count++);
    // }
    int a;
    int b;
    int c;
    sscanf("10, 20, 30", "%d, %d, %d", &a, &b, &c);
    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("c: %d\n", c);

    
    close_file_with_check(&fp);
}

#ifdef _TEST_
void chapt_15_demo_run(void)
{
    print_dividing_line("chapt_15_demo_run");
    // std_out_test();
    // file_read_test();
    // gets_test();
    // scanf_test();
    // bit_write_test();
    random_write_test();
    print_dividing_line("");
}
#endif