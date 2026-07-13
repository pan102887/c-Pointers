#ifndef CP_TEST_H
#define CP_TEST_H

#include <stddef.h>

typedef void (*cp_test_func)(void);

typedef struct cp_test_case {
    const char *name;
    cp_test_func run;
} cp_test_case;

typedef struct cp_test_result {
    size_t total;
    size_t passed;
    size_t failed;
} cp_test_result;

void cp_test_fail(const char *file, int line, const char *expr);
int cp_test_main(int argc, char **argv, const cp_test_case *tests, size_t tests_size);

#define CP_TEST_ASSERT(expr)                                                   \
    do {                                                                       \
        if (!(expr)) {                                                         \
            cp_test_fail(__FILE__, __LINE__, #expr);                           \
            return;                                                            \
        }                                                                      \
    } while (0)

#define CP_TEST_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#endif // CP_TEST_H
