#ifndef _B_TREE_2_H_
#define _B_TREE_2_H_

#include <stddef.h>

typedef struct _b_tree_2_node_
{
    void *key;
    void *value;

    size_t height;

    struct _b_tree_2_node_ *left;
    struct _b_tree_2_node_ *right;
} b_tree_2_node;

typedef struct _b_tree_2_
{
    size_t height;
    size_t size;
    b_tree_2_node *root;
    int (*key_compare)(const void *, const void *);
} b_tree_2;

typedef enum
{
    INSERT_SUCCESS,
    INSERT_FAILURE,
} b_tree_insert_result;

typedef enum
{
    DELETE_FAILURE,
    DELETE_SUCCESS,
} b_tree_delete_result;

extern b_tree_2 *b_tree_2_new(int (*key_compare)(const void *, const void *));
extern b_tree_insert_result b_tree_2_insert(b_tree_2 *tree, void *key, void *value);
extern b_tree_delete_result b_tree_2_delete(b_tree_2 *tree, void *key);
extern void *b_tree_2_search(b_tree_2 *tree, void *key);
extern void b_tree_2_free(b_tree_2 *tree);

#endif