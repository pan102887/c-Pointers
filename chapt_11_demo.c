#include "chapt_11_demo.h"

#include "global.h"
#include "alloc.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void memory_alloc_test() {
    print_dividing_line("memory_alloc_test");
    int *array = MALLOC(10, int);
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    assert(NULL != array);
    FREE(&array);
    assert(NULL == array);
    multi_dividing_line(2, "memory_alloc_test", "end");
}

#ifdef _TEST_
extern void chapt_11_demo_run() {
    const char *title = "chapt_11_demo";
    print_dividing_line(title);
    memory_alloc_test();
    multi_dividing_line(2, title, "end");
}
#endif