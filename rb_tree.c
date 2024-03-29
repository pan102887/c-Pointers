#include "rb_tree.h"
#include "alloc.h"
#include "m_array_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <assert.h>


typedef size_t rb_count_t;
typedef enum rb_color
{
    RED,
    BLACK
} color_t;

typedef struct rb_node
{
    color_t color;
    /*7 Byte between color and key*/
    rb_internal_key_type key;
    rb_internal_value_type value;
    rb_count_t node_count;

    struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;
} rb_node, *rb_node_ptr;

static inline color_t node_color(rb_node_ptr node);
static inline bool is_red(rb_node_ptr node);
static inline void flip_color(rb_node_ptr node);
static inline rb_count_t size(rb_node_ptr node);
static inline void set_parent(rb_node_ptr node, rb_node_ptr parent);
static inline void rotate_left(rb_node_ptr *root_pp);
static inline void rotate_right(rb_node_ptr *root_pp);
static inline rb_node_ptr node_create(rb_internal_key_type key, rb_internal_value_type value, color_t color, rb_count_t count);
static inline rb_node_ptr insert_into_node(rb_node_ptr *h_p, rb_internal_key_type key, rb_internal_value_type value, key_compare_f compare);
static inline void node_destroy(rb_node_ptr *node_pp, rb_desctroy_f destroy);


static inline color_t node_color(rb_node_ptr node)
{
    if (NULL == node)
    {
        return BLACK;
    }
    return node->color == RED ? RED : BLACK;
}

static inline bool is_red(rb_node_ptr node)
{
    return node_color(node) == RED;
}

static inline void flip_color(rb_node_ptr node)
{
    if (NULL == node)
    {
        return;
    }
    node->color = node->color == RED ? BLACK : RED;
    if (NULL != node->left)
    {
        node->left->color = node->color == RED ? BLACK : RED;
    }
    if (NULL != node->right)
    {
        node->right->color = node->color == RED ? BLACK : RED;
    }
}

static inline rb_count_t size(rb_node_ptr node)
{
    if (NULL == node)
    {
        return 0;
    }
    return node->node_count;
}

static inline void set_parent(rb_node_ptr node, rb_node_ptr parent)
{
    if (NULL != node)
    {
        node->parent = parent;
    }
}

static inline void rotate_left(rb_node_ptr *root_pp)
{
    if (NULL == root_pp || NULL == *root_pp)
    {
        return;
    }
    rb_node_ptr root = *root_pp;
    rb_node_ptr right = root->right;
    if (NULL == right)
    {
        return;
    }

    color_t root_color = root->color;
    root->color = right->color;
    right->color = root_color;

    rb_node_ptr root_parent = root->parent;
    root->right = right->left;
    set_parent(root->right, root);
    right->left = root;
    set_parent(root, right);
    *root_pp = right;
    set_parent(right, root_parent);

    right->node_count = root->node_count;
    root->node_count = size(root->left) + size(root->right) + 1;
}

static inline void rotate_right(rb_node_ptr *root_pp)
{
    if (NULL == root_pp || NULL == *root_pp)
    {
        return;
    }
    rb_node_ptr root = *root_pp;
    rb_node_ptr left = root->left;
    if (NULL == left)
    {
        return;
    }

    color_t root_color = root->color;
    root->color = left->color;
    left->color = root_color;

    rb_node_ptr root_parent = root->parent;
    root->left = left->right;
    set_parent(root->left, root);
    left->right = root;
    set_parent(root, left);
    *root_pp = left;
    set_parent(left, root_parent);

    left->node_count = root->node_count;
    root->node_count = size(root->left) + size(root->right) + 1;
}

static inline rb_node_ptr node_create(rb_internal_key_type key, rb_internal_value_type value, color_t color, rb_count_t count)
{
    rb_node_ptr node = NEW(rb_node, 1);
    node->color = color;
    node->key = key;
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->node_count = count;
    return node;
}

static inline rb_node_ptr insert_into_node(rb_node_ptr *h_p, rb_internal_key_type key, rb_internal_value_type value, key_compare_f compare)
{
    if (NULL == h_p)
    {
        return NULL;
    }
    rb_node_ptr h = *h_p;
    if (NULL == h)
    {
        return node_create(key, value, RED, 1);
    }
    int cmp = compare(key, h->key);
    if (cmp < 0)
    {
        h->left = insert_into_node(&(h->left), key, value, compare);
        set_parent(h->left, h);
    }
    else if (cmp > 0)
    {
        h->right = insert_into_node(&(h->right), key, value, compare);
        set_parent(h->right, h);
    }
    else
    {
        h->value = value;
    }

    if (is_red(h->right) && !is_red(h->left))
    {
        rotate_left(&h);
    }
    if (is_red(h->left) && is_red(h->left->left))
    {
        rotate_right(&h);
    }
    if (is_red(h->left) && is_red(h->right))
    {
        flip_color(h);
    }
    h->node_count = size(h->left) + size(h->right) + 1;
    return h;
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
    rb_node_ptr node_left = ((*node_pp)->left);
    rb_node_ptr node_right = ((*node_pp)->right);
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
extern void rb_tree_insert(rb_tree_ptr entry, rb_key_type key, rb_value_type value)
{
    if (NULL == entry || NULL == key)
    {
        fprintf(stderr, "Invalid argument\n");
        return;
    }
    rb_internal_key_type internal_key = entry->kcpy(key);
    rb_internal_value_type internal_value = entry->vcpy(value);
    entry->root = insert_into_node((rb_node_ptr*)&(entry->root), internal_key, internal_value, entry->compare);
}
extern rb_value_type rb_tree_search(rb_tree_ptr entry, rb_key_type key)
{
    if (NULL == entry || NULL == entry->root)
    {
        return NULL;
    }
    rb_node_ptr node = entry->root;
    while (NULL != node)
    {
        int cmp = entry->compare(key, node->key);
        if (cmp < 0)
        {
            node = node->left;
        }
        else if (cmp > 0)
        {
            node = node->right;
        }
        else
        {
            return node->value;
        }
    }
    return NULL;
}
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

static void create_destroy_test()
{
    rb_tree_ptr entry = NULL;
    entry = rb_tree_create(cmpare, kcpy, vcpy, destroy);
    assert(NULL != entry);
    rb_tree_destroy(&entry);
    assert(NULL == entry);
}
/**
 * @brief 
 * 
 *                    o (root_parent)                                      o (root_parent)
 *                   /                                                    /               
 *      (root_left) o---o (root_right)        ==>        (root_left) o---o (root_right)   
 *                 /   / \                                          / \   \               
 *         (left) o   o   o (right)                         (left) o   o   o (right)      
 *                 (midle)                                          (midle)               
 */
static void rotate_left_test()
{
    rb_node_ptr root_parent = node_create("root_parent", "root_parent", BLACK, 6);
    rb_node_ptr root_left = node_create("root_left", "root_left", BLACK, 5);
    rb_node_ptr root_right = node_create("root_right", "root_right", BLACK, 3);

    rb_node_ptr left = node_create("left", "left", BLACK, 1);
    rb_node_ptr right = node_create("right", "right", BLACK, 1);
    rb_node_ptr midile = node_create("midle", "midle", BLACK, 1);

    root_parent->left = root_left;
    root_left->parent = root_parent;

    root_left->right = root_right;
    root_right->parent = root_left;
    root_left->left = left;
    left->parent = root_left;

    root_right->left = midile;
    midile->parent = root_right;
    root_right->right = right;
    right->parent = root_right;

    root_left->color = BLACK;
    root_right->color = RED;

    left->node_count = 1;
    midile->node_count = 1;
    right->node_count = 3;
    root_right->node_count = size(root_right->left) + size(root_right->right) + 1;
    root_left->node_count = size(root_left->left) + size(root_left->right) + 1;
    root_parent->node_count = size(root_parent->left) + size(root_parent->right) + 1;
    assert(root_right->node_count == 5);
    assert(root_left->node_count = 7);

    rotate_left(&(root_parent->left));

    assert(root_parent->left == root_right);
    assert(root_right->parent == root_parent);

    assert(root_right->left == root_left);
    assert(root_left->parent == root_right);

    assert(root_right->right == right);
    assert(right->parent == root_right);

    assert(root_left->right == midile);
    assert(midile->parent == root_left);

    assert(root_left->left == left);
    assert(left->parent == root_left);

    assert(root_right->color == BLACK);
    assert(root_left->color == RED);

    assert(root_left->node_count = 3);
    assert(root_right->node_count == 7);

    node_destroy(&root_parent, NULL);

    rb_node_ptr root = node_create("root", "root", BLACK, 10);
    rotate_left(&root);
    assert(NULL != root);
    node_destroy(&root, NULL);
}

extern void rb_tree_test()
{
    create_destroy_test();
    rotate_left_test();
}
#endif