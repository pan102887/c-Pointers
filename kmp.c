#include "kmp.h"

#include "global.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static size_t search(kmp *self, char* str) {
    return -1;
}

void init_dfa( char (*dfa)[256], const char *pattern){
    size_t pattern_len = strlen(pattern);
    dfa = malloc(sizeof(char) * pattern_len * 256);
}

void kmp_new(kmp *this, const char* pattern) {
    this = malloc(sizeof(kmp));
    this -> pattern_len = strlen(pattern);
    init_dfa(this -> dfa, pattern);
    this -> seach = search;
}

void kmp_delete(kmp *this) {
    if (NULL == this) {
        return;
    }
    if (NULL != this -> dfa) {
        free(this -> dfa);
    }
    free(this);
}


#ifdef _TEST_
static const char* title = "kmp test";

void kmp_new_test() {
    size_t size = sizeof(kmp);
    printf("size of kmp: %ld\n", size);
    
    kmp* k; 
    kmp_new(k, "test");
    printf("kmp address: \t\t%p\n", k);

    size_t *pattern_len_address = &(k->pattern_len);
    printf("pattern_len address: \t%p\n", pattern_len_address);

    char (**dfa_address)[256] = &(k->dfa);
    printf("dfa address: \t\t%p\n", dfa_address);

    size_t (**search_address)(kmp *, char*) = &(k->seach);
    printf("search address: \t%p\n", search_address);
}

void kmp_test() {
    print_dividing_line(title);
    kmp_new_test();
    print_dividing_line("");
}
#endif