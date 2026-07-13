#include "cp_test.h"

#include "chapt_7_practice.h"

void chapter_07_math_tests(void)
{
    CP_TEST_ASSERT(hermite(3, 2) == 40);
    CP_TEST_ASSERT(my_gcd(6, 3) == 3);
    CP_TEST_ASSERT(my_gcd(6, 4) == 2);
    CP_TEST_ASSERT(ascii_to_integer("123") == 123);
    CP_TEST_ASSERT(max_list(4, 3, 2, 5, 6) == 6);
}
