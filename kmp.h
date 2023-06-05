#ifndef _KMP_H_
#define _KMP_H_
#include <stddef.h>

typedef struct kmp
{
    size_t pattern_len;
    char (*dfa)[256];
    size_t (*seach)(struct kmp *self, char *str);
} kmp;

void kmp_new(kmp *this, const char *pattern);
void kmp_delete(kmp *this);

#ifdef _TEST_
void kmp_test();
#endif

#endif