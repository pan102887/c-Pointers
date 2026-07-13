#include "cp_test.h"

#include <stdio.h>
#include <string.h>

static cp_test_result current_result;

void cp_test_fail(const char *file, int line, const char *expr)
{
    current_result.failed++;
    printf("    assertion failed: %s:%d: %s\n", file, line, expr);
}

static void list_tests(const cp_test_case *tests, size_t tests_size)
{
    for (size_t i = 0; i < tests_size; i++) {
        printf("%zu: %s\n", i, tests[i].name);
    }
}

static const cp_test_case *find_by_name(
    const cp_test_case *tests,
    size_t tests_size,
    const char *name)
{
    for (size_t i = 0; i < tests_size; i++) {
        if (strcmp(tests[i].name, name) == 0) {
            return &tests[i];
        }
    }
    return NULL;
}

static int run_one(const cp_test_case *test)
{
    size_t failed_before = current_result.failed;

    printf("[ RUN      ] %s\n", test->name);
    test->run();
    current_result.total++;

    if (current_result.failed == failed_before) {
        current_result.passed++;
        printf("[       OK ] %s\n", test->name);
        return 0;
    }

    printf("[  FAILED  ] %s\n", test->name);
    return 1;
}

static int run_all(const cp_test_case *tests, size_t tests_size)
{
    int failed = 0;
    for (size_t i = 0; i < tests_size; i++) {
        if (strncmp(tests[i].name, "DISABLED_", 9) == 0) {
            printf("[ DISABLED ] %s\n", tests[i].name);
            continue;
        }
        failed += run_one(&tests[i]);
    }
    return failed;
}

static int run_by_index(const cp_test_case *tests, size_t tests_size, const char *index_text)
{
    int index = 0;
    for (size_t i = 0; index_text[i] != '\0'; i++) {
        if (index_text[i] < '0' || index_text[i] > '9') {
            printf("invalid test index: %s\n", index_text);
            return 1;
        }
        index = index * 10 + (index_text[i] - '0');
    }

    if (index < 0 || (size_t) index >= tests_size) {
        printf("can not find test index: %d\n", index);
        return 1;
    }

    return run_one(&tests[index]);
}

static int run_by_name(const cp_test_case *tests, size_t tests_size, const char *name)
{
    const cp_test_case *test = find_by_name(tests, tests_size, name);
    if (test == NULL) {
        printf("can not find test: %s\n", name);
        return 1;
    }

    return run_one(test);
}

static void print_usage(const char *program)
{
    printf("usage: %s [--list | --run_all | -n name | -i index]\n", program);
}

int cp_test_main(int argc, char **argv, const cp_test_case *tests, size_t tests_size)
{
    current_result = (cp_test_result){0};

    if (argc == 1 || strcmp(argv[1], "--run_all") == 0) {
        run_all(tests, tests_size);
    } else if (strcmp(argv[1], "--list") == 0) {
        list_tests(tests, tests_size);
        return 0;
    } else if (strcmp(argv[1], "-n") == 0 && argc >= 3) {
        run_by_name(tests, tests_size, argv[2]);
    } else if (strcmp(argv[1], "-i") == 0 && argc >= 3) {
        run_by_index(tests, tests_size, argv[2]);
    } else {
        print_usage(argv[0]);
        return 1;
    }

    printf("[==========] %zu tests ran. %zu passed. %zu failed.\n",
           current_result.total,
           current_result.passed,
           current_result.failed);

    return current_result.failed == 0 ? 0 : 1;
}
