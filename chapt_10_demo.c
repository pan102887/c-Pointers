#include "chapt_10_demo.h"

#include "global.h"

#include <stddef.h>
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
} A;

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
} B;

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

/**
 * @brief 内存边界对齐测试
 *
 *        1.第一个成员在结构体变量偏移量为0 的地址处，也就是第一个成员必须从头开始。
 *        2.以后每个成员相对于结构体首地址的 offset 都是该成员大小的整数倍，如有需要编译器会在成员之间加上填充字节。
 *        3.结构体的总大小为 最大对齐数的整数倍（每个成员变量都有自己的对齐数），如有需要编译器会在最末一个成员之后加上填充字节。
 *        4.如果嵌套结构体，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小就是所有最大对齐数（包含嵌套结构体的对齐数）的整数倍。
 */
void memory_boundary_alignment_test()
{
    static const char *memory_boundary_alignment = "memory boundary alignment";
    print_dividing_line(memory_boundary_alignment);

    printf("struct A size: %ld\n", sizeof(struct A));
    A a = {'a', 1, 2};
    printf("a address: %p\n", &a);
    printf("a.a address: %p\t offset: %ld\t size: %ld\n", &a.a, offsetof(A, a), sizeof(a.a));
    printf("a.b address: %p\t offset: %ld\t size: %ld\n", &a.b, offsetof(A, b), sizeof(a.b));
    printf("a.c address: %p\t offset: %ld\t size: %ld\n", &a.c, offsetof(A, c), sizeof(a.c));
    printf("\n");

    printf("struct B size: %ld\n", sizeof(struct B));
    B b = {2, 'a', 1};
    printf("b address: %p\n", &b);
    printf("b.a address: %p\t offset: %ld\t szie: %ld\n", &b.a, offsetof(B, a), sizeof(b.a));
    printf("b.b address: %p\t offset: %ld\t size: %ld\n", &b.b, offsetof(B, b), sizeof(b.b));
    printf("b.c address: %p\t offset: %ld\t size: %ld\n", &b.c, offsetof(B, c), sizeof(b.c));
    printf("\n");

    printf("struct C size: %ld\n", sizeof(struct C));
    C c = {'a', 1, 2, 3};
    printf("c address: %p\n", &c);
    printf("c.a address: %p\t offset: %ld\t size: %ld\n", &c.a, offsetof(C, a), sizeof(c.a));
    printf("c.b address: %p\t offset: %ld\t size: %ld\n", &c.b, offsetof(C, b), sizeof(c.b));
    printf("c.c address: %p\t offset: %ld\t size: %ld\n", &c.c, offsetof(C, c), sizeof(c.c));
    printf("c.d address: %p\t offset: %ld\t size: %ld\n", &c.d, offsetof(C, d), sizeof(c.d));
    printf("\n");

    printf("struct D size: %ld\n", sizeof(struct D));
    D d = {a, c, b};
    printf("d address: %p\n", &d);
    printf("d.a address: %p\t offset: %ld\t size: %ld\n", &d.a, offsetof(D, a), sizeof(d.a));
    printf("d.b address: %p\t offset: %ld\t size: %ld\n", &d.b, offsetof(D, b), sizeof(d.b));
    printf("d.c address: %p\t offset: %ld\t size: %ld\n", &d.c, offsetof(D, c), sizeof(d.c));
    printf("\n");
    multi_dividing_line(2, memory_boundary_alignment, "end");
}

/**
 * @brief 结构体E
 *        内存分布为： |  a |  b |         c         |    d    |
 *                    |aaaa|bbbb|cccc cccc cccc cccc|dddd dddd|
 *                    |4bit|4bit|       16bit       |   8bit  |
 *                    |    1B   |    1B   |    1B   |    1B   |
 * 
 */
typedef struct E
{
    unsigned int a : 4;
    unsigned int b : 4;
    int c : 16;
    short d : 8;
} E;

/**
 * @brief 位段测试
 *        位段的声明和结构体成员的声明类似，但是它的成员是一个或者多个位的字段，
 *        这些不同长度的字段实际存储于一个或者多个整形变量中。
 *
 *        位段的声明形式和结构体成员的声明形式相同，只是在成员名后面跟一个冒号
 *        和一个整数，这个整数指定这个位段所占用的位的数目。并且位段成员必须声
 *        明为 int, signed int或者 unsigned int 类型(short int,
 *        unsigned short int也可)。
 *
 *        考虑可移植性的程序应该避免使用位段，因为位段在不同的系统中可能有不同
 *        的结果.
 *        1. 缺省符号声明的类型在不同的机器上可能是有符号的，也可能是无符号的。
 *
 *        2. 位段中的位最大数目在不同的机器上不相同，例如在32位机器上的一个位
 *           段声明，可能在16位机器上无法运行。
 */
void bit_field_test()
{
    const char *bit_field_test = "bit filed test";
    print_dividing_line(bit_field_test);
    E e = { 0xF, 1, 0x8000, 0x80};
    printf("struct E size: \t%ld\n", sizeof(struct E));
    printf("e address: \t%p\n", &e);
    printf("e.a: \t\t%d\n", e.a);
    printf("e.b: \t\t%d\n", e.b);
    printf("e.c: \t\t%d\n", e.c);
    printf("e.d: \t\t%d\n", e.d);
    multi_dividing_line(2, bit_field_test, "end");
}

typedef union U
{
    int a;
    char b;
}U;

/**
 * @brief 共用体测试
 *        共用体（联合）的所有成员引用的是内存中的相同位置
 * 
 */
void union_test()
{
    const char *union_test = "union test";
    print_dividing_line(union_test);
    U u;
    u.a = 0x0000000F;
    printf("szieof(U): \t%ld Byte\n", sizeof(U));
    printf("sizeof(U.a): \t%ld Byte\n", sizeof(u.a));
    printf("sizeof(U.b): \t%ld Byte\n", sizeof(u.b));

    printf("u.a: \t\t0x%x\n", u.a);
    printf("u.b: \t\t0x%x\n", u.b);
    u.b = 'a';
    printf("u.a: \t\t0x%x\n", u.a);
    printf("u.b: \t\t0x%x\n", u.b);
    multi_dividing_line(2, union_test, "end");
}


#ifdef _TEST_
static const char *title = "chapt_10_demo";
void chapt_10_demo_run()
{
    print_dividing_line(title);
    memory_boundary_alignment_test();
    bit_field_test();
    union_test();
    print_dividing_line("");
}
#endif