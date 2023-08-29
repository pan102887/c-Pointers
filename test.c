#include "test.h"

#ifdef _TEST_
#include "runable.h"
#include "global.h"
#include "chapt_7_practice.h"
#include "chapt_8_demo.h"
#include "chapt_8_practice.h"
#include "linked_list.h"
#include "eight_queens.h"
#include "chapt_9_demo.h"
#include "chapt_10_demo.h"
#include "chapt_11_demo.h"
#include "chapt_12_demo.h"
#include "chapt_13_demo.h"
#include "chapt_14_demo.h"
#include "chapt_15_demo.h"
#include "b_tree.h"
#include "kmp.h"

#include <stdio.h>
#include <string.h>

static const Runable runable_list[] = {
    {chapt_7_practice_run, "chapt_7_practice_run"},
    {chapt_8_demo_run, "chapt_8_demo_run"},
    {chapt_8_practice_run, "chapt_8_practice_run"},
    {chapt_9_demo_run, "chapt_9_demo_run"},
    {eight_queens_test, "eight_queens_test"},
    {kmp_test, "kmp_test"},
    {chapt_10_demo_run, "chapt_10_demo_run"},
    {chapt_11_demo_run, "chapt_11_demo_run"},
    {chapt_12_demo_test, "chapt_12_demo_test"},
    {chapt_13_demo_run, "chapt_13_demo_run"},
    {chapt_14_demo_run, "chapt_14_demo_run"},
    {chapt_15_demo_run, "chapt_15_demo_run"},
    {b_tree_test, "b_tree_test"}
};

static const size_t runable_list_size = 13;

static char const *const cmds[] = {
    "-n",
    "-i",
    "--list",
    "--run_all"};
static const size_t cmds_size = 4;

// ---------------------------------------------------------------

static void list_runnable(int argc, char **argv)
{
    for (int i = 0; i < runable_list_size; i++)
    {
        printf("%d: %s\n", i, runable_list[i].name);
    }
}

static void run_all(int argc, char **argv)
{
    for (int i = 0; i < runable_list_size; i++)
    {
        runable_list[i].run();
    }
}

static Runable *find_by_name(char const *const name)
{
    for (int i = 0; i < runable_list_size; i++)
    {
        if (strcmp(runable_list[i].name, name) == 0)
        {
            return (Runable *)&runable_list[i];
        }
    }
    return NULL;
}

static void run_by_name(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("please input the name of the runable\n");
        return;
    }

    Runable *runable = find_by_name(argv[2]);
    if (runable == NULL)
    {
        printf("can not find the runable\n");
        return;
    }
    runable->run();
    return;
}

static int string2int(char *str)
{
    int result = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

static void run_by_index(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("please input the index of the runable\n");
        return;
    }
    int index = string2int(argv[2]);
    if (index < 0 || index >= runable_list_size)
    {
        printf("can not find the runable\n");
        return;
    }
    runable_list[index].run();
    return;
}

static void first_command_excutor(int argc, char **argv)
{
    void (*func[])(int, char **) = {
        run_by_name,
        run_by_index,
        list_runnable,
        run_all};

    for (int i = 0; i < cmds_size; i++)
    {
        if (strcmp(cmds[i], argv[1]) == 0)
        {
            func[i](argc, argv);
            return;
        }
    }
}

static int is_valide_command(const char const *command)
{
    for (int i = 0; i < cmds_size; i++)
    {
        if (strcmp(cmds[i], command) == 0)
        {
            return 1;
        }
    }
    return 0;
}

extern void test_run(int argc, char **argv)
{
    if (argc == 1)
    {
        run_all(argc, argv);
        return;
    }
    if (argc < 2 || !is_valide_command(argv[1]))
    {
        printf("please run with valid command: ");
        for (int i = 0; i < cmds_size; i++)
        {
            printf("%s, ", cmds[i]);
        }
        printf("\n");
        return;
    }
    first_command_excutor(argc, argv);
}
#endif // _TEST_