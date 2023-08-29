#include "b_tree.h"

#include <stdlib.h>
#include <stdio.h>

static inline b_tree_node *alloc_b_tree_node(int key, void *value);
static inline void b_tree_node_insert(b_tree_node **root, int key, void *value);
static inline void b_tree_subtree_free(b_tree_node **root);
static inline void b_tree_node_delete(b_tree_node **root, int key);
static inline void b_tree_node_free(b_tree_node **node);
static inline void b_tree_node_print(b_tree_node *tree);

extern b_tree *b_tree_new()
{
    b_tree *tree = malloc(sizeof(b_tree));
    tree->root = NULL;
    return tree;
}

extern void b_tree_insert(b_tree *tree, int key, void *value)
{
    if (NULL == tree)
    {
        return;
    }
    b_tree_node_insert(&(tree->root), key, value);
}

static inline void b_tree_node_insert(b_tree_node **root, int key, void *value)
{
    if (NULL == root)
    {
        return;
    }
    b_tree_node **insert_position = root;
    while(*insert_position != NULL)
    {
        if (key < (*insert_position)-> key)
        {
            insert_position = &((*insert_position)->left);
        }
        else if (key > (*insert_position)->key)
        {
            insert_position = &((*insert_position)->right);
        }
        else
        {
            (*insert_position)->value = value;
            return;
        }
    }
    *insert_position = alloc_b_tree_node(key, value);
}
static inline b_tree_node *alloc_b_tree_node(int key, void *value)
{
    b_tree_node *node = malloc(sizeof(b_tree_node));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}


extern void b_tree_delete(b_tree *tree, int key)
{
    if (NULL == tree)
    {
        return;
    }
    b_tree_node_delete(&(tree->root), key);
}
static inline void b_tree_node_delete(b_tree_node **root, int key)
{
    if (NULL == root || NULL == *root)
    {
        return;
    }
    b_tree_node **delete_position = root;
    while (*delete_position != NULL)
    {
        if (key < (*delete_position)->key)
        {
            delete_position = &((*delete_position)->left);
        }
        else if (key > (*delete_position)->key)
        {
            delete_position = &((*delete_position)->right);
        }
        else
        {
            break;
        }
    }
    if (NULL == *delete_position)
    {
        return;
    }
    b_tree_node_free(delete_position);
}

static inline void b_tree_node_free(b_tree_node **node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }

    if ((*node)->left == NULL && (*node)->right == NULL)
    {
        free(*node);
        *node = NULL;
    }
    else if ((*node)->left == NULL)
    {
        b_tree_node *temp = *node;
        *node = (*node)->right;
        free(temp);
    }
    else if ((*node)->right == NULL)
    {
        b_tree_node *temp = *node;
        *node = (*node)->left;
        free(temp);
    }
    else
    {
        b_tree_node **successor = &((*node)->right);
        while ((*successor)->left != NULL)
        {
            successor = &((*successor)->left);
        }
        (*node)->key = (*successor)->key;
        b_tree_node_free(successor);
    }
}

extern b_tree_node *b_tree_search(b_tree *tree, int key)
{
    if (NULL == tree || NULL == tree->root)
    {
        return NULL;
    }
    b_tree_node *current = tree->root;
    while (current != NULL)
    {
        if (key < current->key)
        {
            current = current->left;
        }
        else if (key > current->key)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
    return NULL;
}

extern void b_tree_print(b_tree *tree)
{
    if (NULL == tree || NULL == tree->root)
    {
        return;
    }
    b_tree_node_print(tree->root);
    printf("\n");
}
static inline void b_tree_node_print(b_tree_node *tree)
{
    if (NULL == tree)
    {
        return;
    }
    b_tree_node_print(tree->left);
    printf("%d ", tree->key);
    b_tree_node_print(tree->right);
}


extern void b_tree_free(b_tree *tree)
{
    if (NULL == tree)
    {
        return;
    }
    b_tree_subtree_free(&(tree->root));
}

static inline void b_tree_subtree_free(b_tree_node **root)
{
    if (NULL == root || NULL == *root)
    {
        return;
    }
    b_tree_subtree_free(&((*root)->left));
    b_tree_subtree_free(&((*root)->right));
    free(*root);
    *root = NULL;
}


#ifdef _TEST_
static inline void search_and_print(b_tree *tree, int key)
{
    b_tree_node *node = b_tree_search(tree, key);
    if (NULL != node)
    {
        printf("find node with key %d and value is: \"%s\"\n", node->key, (char *)node->value);
    }
    else
    {
        printf("can not find node\n");
    }
}

void b_tree_test()
{
    b_tree *tree = b_tree_new();
    b_tree_insert(tree, 5, "demo");
    b_tree_insert(tree, 3, "sdf");
    b_tree_insert(tree, 7, "test");
    b_tree_insert(tree, 2, "what the fuck");
    b_tree_insert(tree, 4, "amazing");
    b_tree_insert(tree, 6, "1");
    b_tree_insert(tree, 8, "2");
    b_tree_insert(tree, 10, "3");
    b_tree_insert(tree, 11, "4");
    b_tree_insert(tree, 1, "5");
    b_tree_insert(tree, 9, "6");

    search_and_print(tree, 2);
    b_tree_insert(tree, 2, "after change");
    search_and_print(tree, 2);


    search_and_print(tree, 12);
    b_tree_print(tree);

    b_tree_delete(tree, 5);
    b_tree_print(tree);

    b_tree_free(tree);
    b_tree_print(tree);
}
#endif