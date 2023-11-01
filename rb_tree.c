#include "rb_tree.h"
#include "alloc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NEW(type,size) MALLOC(size,type)


typedef bool color_t;
typedef size_t rb_count_t;
static const color_t RED = true;
static const color_t BLACK = false;

typedef struct rb_node
{
    color_t color;
    /*7 Byte between color and key*/
    rb_internal_key_type key;
    rb_internal_value_type value;
    rb_count_t node_count;

    // struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;
} rb_node, *rb_node_ptr;

static inline color_t node_color(rb_node_ptr node);
static inline void rebalance(rb_node_ptr *root_pp);
static inline rb_node_ptr node_create(rb_internal_key_type key, rb_internal_value_type value);
static inline void node_destroy(rb_node_ptr *node_pp, rb_desctroy_f destroy);

static inline color_t node_color(rb_node_ptr node)
{
    if (NULL == node)
    {
        return BLACK;
    }
    return node->color == RED ? RED : BLACK;
}

static inline void rebalance(rb_node_ptr *root_pp)
{
    if (NULL == root_pp || NULL == *root_pp)
    {
        return;
    }
    rb_node_ptr root = *root_pp;
    if (RED != node_color(root->right))
    {
        return;
    }
    root->right = root->right->left;
    // root->right->parent = root;
    root->right->left = root;
    // root->right->parent = root->parent;
    // root->parent = root->right;
    *root_pp = root->right;
    
    root = *root_pp;
    root->left->color = RED;
}

static inline rb_node_ptr node_create(rb_internal_key_type key, rb_internal_value_type value)
{
    rb_node_ptr node = NEW(rb_node, 1);
    node->color = RED;
    node->key = key;
    node->value = value;
    // node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline void node_destroy(rb_node_ptr *node_pp, rb_desctroy_f destroy)
{
    if (NULL == node_pp || NULL == *node_pp)
    {
        return;
    }
    if (NULL != destroy)
    {
        destroy(&((*node_pp)->key), &((*node_pp)->value));
    }
    node_destroy(&((*node_pp)->left), destroy);
    node_destroy(&((*node_pp)->right), destroy);
    FREE(node_pp);
}

extern rb_tree_ptr rb_tree_create(key_compare_f compare, rb_key_cpy_f kcpy, rb_value_cpy_f vcpy, rb_desctroy_f destroy)
{
    if (NULL == compare || NULL == kcpy || NULL == vcpy || NULL == destroy)
    {
        fprintf(stderr, "Invalid argument\n");
        return NULL;
    }
    rb_tree_ptr entry = NEW(rb_entry, 1);
    entry->compare = compare;
    entry->kcpy = kcpy;
    entry->vcpy = vcpy;
    entry->destroy = destroy;
    entry->root = NULL;
    return entry;
}
extern void rb_tree_destroy(rb_tree_ptr *entry)
{
    if (NULL == entry || NULL == *entry)
    {
        return;
    }
    node_destroy((rb_node_ptr *)(&((*entry)->root)), (*entry)->destroy);
    FREE(entry);
}
extern void rb_tree_insert(rb_tree_ptr entry, rb_key_type key, rb_value_type value);
extern rb_value_type rb_tree_search(rb_tree_ptr entry, rb_key_type key);
extern void rb_tree_delete(rb_tree_ptr entry, rb_key_type key);

#ifdef _TEST_
#include <string.h>
#include <assert.h>

static const key_compare_f const cmpare = (key_compare_f)strcmp;
static const rb_key_cpy_f const kcpy = (rb_key_cpy_f)strdup;
static const rb_value_cpy_f const vcpy = (rb_value_cpy_f)strdup;
static inline void destroy(rb_internal_key_type *k_pp, rb_internal_value_type *v_pp)
{
    assert(NULL != k_pp);
    assert(NULL != v_pp);
    assert(NULL != *k_pp);
    assert(NULL != *v_pp);
    FREE(k_pp);
    FREE(v_pp);
    assert(NULL == *k_pp);
    assert(NULL == *v_pp);
}

static inline void create_destroy_test()
{
    rb_tree_ptr entry = NULL;
    entry = rb_tree_create(cmpare, kcpy, vcpy, destroy);
    assert(NULL != entry);
    rb_tree_destroy(&entry);
    assert(NULL == entry);
}

extern void rb_tree_test()
{
    create_destroy_test();
}
#endif