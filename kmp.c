#include "kmp.h"

#include "global.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static size_t search(kmp *this, char *str);
void kmp_init(kmp *this, const char *pattern);
void kmp_delete(kmp *this);
void allocate_dfa_memory(kmp *this);
void init_dfa(kmp *this, const char *pattern);

static size_t search(kmp *this, char *str)
{
    int i, j, N = strlen(str), m = this->pattern_len;
    for (i = 0, j = 0; i < N && j < m; i++)
    {
        j = this->dfa[(int)str[i]][j];
    }
    if (j == m)
    {
        return i - m;
    }
    else
    {
        return -1;
    }
}

void allocate_dfa_memory(kmp *this)
{
    this->dfa = malloc(CHARACTERS * sizeof(int *));
    for (size_t i = 0; i < CHARACTERS; i++)
    {
        this->dfa[i] = malloc(sizeof(int) * this->pattern_len);
    }
}

void init_dfa(kmp *this, const char *pattern)
{
    size_t pattern_len = this->pattern_len;
    allocate_dfa_memory(this);

    this->dfa[pattern[0]][0] = 1;
    for (int x = 0, j = 1; j < pattern_len; j++)
    {
        for (int c = 0; c < CHARACTERS; c++)
        {
            this->dfa[c][j] = this->dfa[c][x];
        }
        this->dfa[pattern[j]][j] = j + 1;
        x = (int)this->dfa[pattern[j]][x];
    }
}

void kmp_init(kmp *this, const char *pattern)
{
    if (NULL == this)
    {
        return;
    }
    this->pattern_len = strlen(pattern);
    init_dfa(this, pattern);
    this->seach = search;
}

void kmp_delete(kmp *this)
{
    if (NULL == this)
    {
        return;
    }
    if (NULL != this->dfa)
    {
        for (size_t i = 0; i < CHARACTERS; i++)
        {
            free(this->dfa[i]);
        }
        free(this->dfa);
    }
}

#ifdef _TEST_
static const char *title = "kmp test";

void kmp_new_test()
{
    size_t size = sizeof(kmp);
    printf("size of kmp: %ld\n", size);

    kmp k;
    kmp_init(&k, "kmp");
    printf("kmp address: \t\t%p\n", &k);

    size_t *pattern_len_address = &(k.pattern_len);
    printf("pattern_len address: \t%p\n", pattern_len_address);

    int ***dfa_address = &(k.dfa);
    printf("dfa address: \t\t%p\n", dfa_address);

    size_t (**search_address)(kmp *, char *) = &(k.seach);
    printf("search address: \t%p\n", search_address);

    printf("\n");

    printf("pattern_len: \t\t%ld\n", k.pattern_len);
    printf("dfa: \t\t\t%p\n", k.dfa);

    char *str = "this is a test string for kmp";
    size_t position = k.seach(&k, str);
    printf("search result: \t\t%ld\n", position);
    printf("search string: \t\t");
    for (size_t i = 0; i < k.pattern_len; i++)
    {
        printf("%c", str[position + i]);
    }
    printf("\n");

    kmp_delete(&k);
}

void kmp_test()
{
    print_dividing_line(title);
    kmp_new_test();
    print_dividing_line("");
}
#endif