#ifndef _B_TREE_H_
#define _B_TREE_H_

typedef struct _b_tree_node {
    int key;
    struct _b_tree_node *left;
    struct _b_tree_node *right;
} b_tree_node;

typedef struct _b_tree {
    b_tree_node *root;
} b_tree;

b_tree *b_tree_new();

void b_tree_insert(b_tree *tree, int key);

void b_tree_delete(b_tree *tree, int key);

b_tree_node *b_tree_search(b_tree *tree, int key);

void b_tree_print(b_tree *tree);

void b_tree_free(b_tree *tree);
#endif