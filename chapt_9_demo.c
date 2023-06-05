#include "chapt_9_demo.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

/**
 * @brief 第九章
 *        字符串、字符和字节
 */

void string_test()
{
    const int size = 10;
    char *str = malloc(size + 1);
    for (int i = 0; i < size; i++)
    {

        str[i] = (char)(i + '1');
    }
    str[size - 1] = '\0';
    // 这里必须保证dst有足够的空间保存str的内容，否则可能会出现段错误
    char *dst = malloc(strlen(str) + 1);
    strcpy(dst, str);
    printf("[string-after-copy]: str: %s\n", str);
    printf("[string-after-copy]: dst: %s\n\n", dst);

    char *spliced;
    // 这里也是必须确保dst的内存空间足够大，否则可能会出现段错误。其内存大小是两个字符串长度的和加一
    dst = realloc(dst, strlen(str) + strlen(dst) + 1);
    printf("string-splice, source: \"%s\" and \"%s\"\n", str, dst);

    printf("[string-befor-splice]: str addr: \t%p\n", str);
    printf("[string-befor-splice]: dst addr: \t%p\n", dst);
    printf("[string-befor-splice]: spliced addr: \t%p\n\n", spliced);

    // strcat函数的返回值是dst的地址，所以这里的spliced和dst是同一个地址
    spliced = strcat(dst, str);
    printf("[string-after-splice]: str addr: \t%p\n", str);
    printf("[string-after-splice]: dst addr: \t%p\n", dst);
    printf("[string-after-splice]: spliced addr: \t%p\n\n", spliced);

    printf("[string-after-splice]: str: %s\n", str);
    printf("[string-after-splice]: dst: %s\n", dst);
    printf("[string-after-splice]: spliced: %s\n\n", spliced);

    printf("[string-after-splice]: dst compare with str: %d\n", strcmp(dst, str));
    printf("[string-after-splice]: str compare with dst: %d\n", strcmp(str, dst));
    printf("[string-after-splice]: dst compare with spliced: %d\n\n", strcmp(dst, spliced));

    free(dst);
    free(str);
}

#ifdef _TEST_
static const char *title = "chapt_9_demo";
void chapt_9_demo_run()
{
    print_dividing_line(title);
    string_test();
    print_dividing_line("");
}
#endif
