#include "b_tree.h"

#include <stdlib.h>

static inline b_tree_node *alloc_b_tree_node(int key);
static inline void b_tree_node_insert(b_tree_node **root, int key);
static inline void b_tree_subtree_free(b_tree_node **root);
static inline void b_tree_node_delete(b_tree_node **root, int key);
static inline void b_tree_node_free(b_tree_node **node);

extern b_tree *b_tree_new()
{
    b_tree *tree = malloc(sizeof(b_tree));
    tree->root = NULL;
    return tree;
}

extern void b_tree_insert(b_tree *tree, int key)
{
    if (NULL == tree)
    {
        return;
    }
    b_tree_node_insert(&(tree->root), key);
}

static inline void b_tree_node_insert(b_tree_node **root, int key)
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
            return;
        }
    }
    *insert_position = alloc_b_tree_node(key);
}
static inline b_tree_node *alloc_b_tree_node(int key)
{
    b_tree_node *node = malloc(sizeof(b_tree_node));
    node->key = key;
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
    if (NULL == tree)
    {
        return;
    }
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


