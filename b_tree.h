#ifndef _B_TREE_H_
#define _B_TREE_H_

#include <stddef.h>

typedef struct _b_tree_node {
    int key;
    void *value;
    struct _b_tree_node *left;
    struct _b_tree_node *right;
} b_tree_node;

typedef struct _b_tree {
    size_t degree;
    size_t height;
    size_t balance;
    b_tree_node *root;
} b_tree;

extern b_tree *b_tree_new();

extern void b_tree_insert(b_tree *tree, int key, void *value);

extern void b_tree_delete(b_tree *tree, int key);

extern b_tree_node *b_tree_search(b_tree *tree, int key);

extern void b_tree_print(b_tree *tree);

extern void b_tree_free(b_tree *tree);

#ifdef _TEST_
extern void b_tree_test();
#endif
#endif