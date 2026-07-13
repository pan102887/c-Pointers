#ifndef CP_CHAPTER_08_DEMO_H
#define CP_CHAPTER_08_DEMO_H

void array_demo(void);
void func_1(int *mat, int row, int col);
void func_2(int mat[3][10]);
int lookup_keyword(char const *const desired_word, char const *keyword_table[], int const size);
double average(int n_value, ...);

#ifdef CP_ENABLE_TESTS
void chapt_8_demo_run();
#endif // CP_ENABLE_TESTS
#endif // CP_CHAPTER_08_DEMO_H