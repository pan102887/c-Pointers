#include "test.h"

#include "global.h"

#include <stdio.h>


/**
 * @brief 结构体A
 *        内存分布为： |  a |  b |  c |
 *                    |a000|bbbb|cc00|
 *                    | 4B | 4B | 4B |
 * 
 */
typedef struct A
{
    char a;
    int b;
    short c;
}A;

/**
 * @brief 结构体B
 *        内存分布为： | ab |  c |
 *                    |aab0|cccc|
 *                    | 4B | 4B |
 */
typedef struct B
{
    short a;
    char b;
    int c;
}B;

/**
 * @brief 结构体C
 *        内存分布为： |    a    |   b    |   cd    |
 *                    |a000 0000|bbb bbbb|cc00 dddd|
 *                    |    8B   |   8B   |   8B    |
 */
typedef struct C
{
    char a;
    long long b;
    short c;
    int d;
} C;

/**
 * @brief 结构体D
 *        内存分布为： |         a         |              b              |    c    |
 *                    |aaaa aaaa|aaaa 0000|bbbb bbbb|bbbb bbbb|bbbb bbbb|cccc cccc|
 *                    |    8B   |    8B   |    8B   |    8B   |    8B   |    8B   |
 */
typedef struct D
{
    A a;
    C b;
    B c;
} D;

static const char* memory_boundary_alignment = "memory boundary alignment";
/**
 * @brief 内存边界对齐测试
 * 
 *        1.第一个成员在结构体变量偏移量为0 的地址处，也就是第一个成员必须从头开始。
 *        2.以后每个成员相对于结构体首地址的 offset 都是该成员大小的整数倍，如有需要编译器会在成员之间加上填充字节。
 *        3.结构体的总大小为 最大对齐数的整数倍（每个成员变量都有自己的对齐数），如有需要编译器会在最末一个成员之后加上填充字节。
 *        4.如果嵌套结构体，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小就是所有最大对齐数（包含嵌套结构体的对齐数）的整数倍。
 */
void memory_boundary_alignment_test() {
    print_dividing_line(memory_boundary_alignment);

    printf("struct A size: %ld\n", sizeof(struct A));
    A a = {'a', 1, 2};
    printf("a address: %p\n", &a);
    printf("a.a address: %p\t offset: %lld\t sizeof a.a: %ld\n", &a.a, ((unsigned long long)&a.a - (unsigned long long)&a), sizeof(a.a));
    printf("a.b address: %p\t offset: %lld\t sizeof a.b: %ld\n", &a.b, ((unsigned long long)&a.b - (unsigned long long)&a), sizeof(a.b));
    printf("a.c address: %p\t offset: %lld\t sizeof a.c: %ld\n", &a.c, ((unsigned long long)&a.c - (unsigned long long)&a), sizeof(a.c));
    printf("\n");
    

    printf("struct B size: %ld\n", sizeof(struct B));
    B b = {2, 'a', 1};
    printf("b address: %p\n", &b);
    printf("b.a address: %p\t offset: %lld\t szieof b.a: %ld\n", &b.a, ((unsigned long long)&b.a - (unsigned long long)&b), sizeof(b.a));
    printf("b.b address: %p\t offset: %lld\t sizeof b.b: %ld\n", &b.b, ((unsigned long long)&b.b - (unsigned long long)&b), sizeof(b.b));
    printf("b.c address: %p\t offset: %lld\t sizeof b.c: %ld\n", &b.c, ((unsigned long long)&b.c - (unsigned long long)&b), sizeof(b.c));
    printf("\n");

    printf("struct C size: %ld\n", sizeof(struct C));
    C c = {'a', 1, 2, 3};
    printf("c address: %p\n", &c);
    printf("c.a address: %p\t offset: %lld\t sizeof c.a: %ld\n", &c.a, ((unsigned long long)&c.a - (unsigned long long)&c), sizeof(c.a));
    printf("c.b address: %p\t offset: %lld\t sizeof c.b: %ld\n", &c.b, ((unsigned long long)&c.b - (unsigned long long)&c), sizeof(c.b));
    printf("c.c address: %p\t offset: %lld\t sizeof c.c: %ld\n", &c.c, ((unsigned long long)&c.c - (unsigned long long)&c), sizeof(c.c));
    printf("c.d address: %p\t offset: %lld\t sizeof c.d: %ld\n", &c.d, ((unsigned long long)&c.d - (unsigned long long)&c), sizeof(c.d));
    printf("\n");

    printf("struct D size: %ld\n", sizeof(struct D));
    D d = {a, c, b};
    printf("d address: %p\n", &d);
    printf("d.a address: %p\t offset: %lld\t sizeof d.a: %ld\n", &d.a, ((unsigned long long)&d.a - (unsigned long long)&d), sizeof(d.a));
    printf("d.b address: %p\t offset: %lld\t sizeof d.b: %ld\n", &d.b, ((unsigned long long)&d.b - (unsigned long long)&d), sizeof(d.b));
    printf("d.c address: %p\t offset: %lld\t sizeof d.c: %ld\n", &d.c, ((unsigned long long)&d.c - (unsigned long long)&d), sizeof(d.c));
    printf("\n");
    
    print_dividing_line("");
}

static const char* test = "test";
void testfunc() {
    print_dividing_line(test);
    memory_boundary_alignment_test();
    print_dividing_line("");
}