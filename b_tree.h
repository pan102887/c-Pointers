#ifndef _B_TREE_H_
#define _B_TREE_H_

#include <stddef.h>

typedef struct _b_tree_node
{
    int key;
    void *value;
    struct _b_tree_node *left;
    struct _b_tree_node *right;
} b_tree_node;

typedef struct _b_tree
{
    size_t height;
    size_t size;
    b_tree_node *root;
} b_tree;

typedef struct _b_tree_node_value_type
{
    void *value;
    void (*free)(void *value);
    int (*compare)(void *value1, void *value2);
} node_value_type;

extern b_tree *b_tree_new();
extern size_t b_tree_height(b_tree *tree);
extern size_t b_tree_size(b_tree *tree);
extern void b_tree_insert(b_tree *tree, int key, void *value);
extern void b_tree_delete(b_tree *tree, int key);
extern b_tree_node *b_tree_search(b_tree *tree, int key);
extern void b_tree_print(b_tree *tree);
extern void b_tree_free(b_tree *tree);

#ifdef _TEST_
extern void b_tree_test();
#endif
#endif