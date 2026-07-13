#include "cp_test.h"

#include "b_tree.h"
#include "chapt_10_demo.h"
#include "chapt_11_demo.h"
#include "chapt_12_demo.h"
#include "chapt_13_demo.h"
#include "chapt_14_demo.h"
#include "chapt_15_demo.h"
#include "chapt_16_demo.h"
#include "chapt_7_practice.h"
#include "chapt_8_demo.h"
#include "chapt_8_practice.h"
#include "chapt_9_demo.h"
#include "eight_queens.h"
#include "kmp.h"
#include "m_array_list.h"
#include "rb_tree.h"
#include "tt_tree.h"

void chapter_07_math_tests(void);

static const cp_test_case tests[] = {
    {"chapter_07_math_tests", chapter_07_math_tests},
    {"chapt_7_practice_run", chapt_7_practice_run},
    {"chapt_8_demo_run", chapt_8_demo_run},
    {"chapt_8_practice_run", chapt_8_practice_run},
    {"chapt_9_demo_run", chapt_9_demo_run},
    {"eight_queens_test", eight_queens_test},
    {"kmp_test", kmp_test},
    {"chapt_10_demo_run", chapt_10_demo_run},
    {"chapt_11_demo_run", chapt_11_demo_run},
    {"chapt_12_demo_test", chapt_12_demo_test},
    {"chapt_13_demo_run", chapt_13_demo_run},
    {"chapt_14_demo_run", chapt_14_demo_run},
    {"chapt_15_demo_run", chapt_15_demo_run},
    {"chapt_16_demo_run", chapt_16_demo_run},
    {"b_tree_test", b_tree_test},
    {"array_list_test", array_list_test},
    {"DISABLED_tt_tree_test", tt_tree_test},
    {"rb_tree_test", rb_tree_test},
};

int main(int argc, char **argv)
{
    return cp_test_main(argc, argv, tests, CP_TEST_ARRAY_SIZE(tests));
}
