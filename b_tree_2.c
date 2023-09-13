#include "b_tree_2.h"

#include "m_def.h"

#include <stdlib.h>
#include <stdio.h>

extern b_tree_2 *b_tree_2_new(int (*key_compare)(const void *, const void *))
{
    b_tree_2 *tree = (b_tree_2 *)malloc(sizeof(b_tree_2));
    if (NULL == tree)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->key_compare = key_compare;
    return tree;
}

extern b_tree_insert_result b_tree_2_insert(b_tree_2 *tree, void *key, void *value)
{
    if (NULL == tree || NULL == key)
    {
        return INSERT_FAILURE;
    }
}