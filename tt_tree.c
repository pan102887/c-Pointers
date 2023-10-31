#include "tt_tree.h"

#include "m_def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW(type) ((type *)malloc_with_check(sizeof(type)))

static inline void *malloc_with_check(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        perror("malloc");
        printf("malloc failed\n");
        exit(1);
    }
    return ptr;
}

typedef enum
{
    TWO_NODE,
    THREE_NODE,
    UNKNOWN
} node_type;

typedef struct tt_tree_node_wrapper
{
    struct tt_tree_node_wrapper *parent;
    node_type type;
    void *node;
} node_wrapper;
typedef struct tt_tree_node_wrapper *node_wrapper_ptr;

typedef struct two_node
{
    key_type key;
    value_type value;
    node_wrapper_ptr left;
    node_wrapper_ptr right;
} two_node;
typedef struct two_node *two_node_ptr;

typedef struct three_node
{
    key_type left_key;
    value_type left_value;
    key_type right_key;
    value_type right_value;
    node_wrapper_ptr left;
    node_wrapper_ptr middle;
    node_wrapper_ptr right;
} three_node;
typedef struct three_node *three_node_ptr;

static inline node_wrapper_ptr node_create();
static inline two_node_ptr two_node_create();
static inline three_node_ptr three_node_create();

static inline void node_destroy(node_wrapper_ptr *node);
static inline void two_node_destroy(two_node_ptr *node);
static inline void three_node_destroy(three_node_ptr *node);
static inline void node_insert(node_wrapper_ptr node, key_type key, value_type value, tt_compare compare);
static inline void insert(node_wrapper_ptr node, key_type key, value_type value, tt_compare compare);
static inline void insert_into_two_node(node_wrapper_ptr node, key_type key, value_type value, node_wrapper_ptr left, node_wrapper_ptr right, tt_compare compare);
static inline void insert_into_three_node(node_wrapper_ptr node, key_type key, value_type value, node_wrapper_ptr left, node_wrapper_ptr right, tt_compare compare);
static inline void set_parent(node_wrapper_ptr node, node_wrapper_ptr parent);

static inline node_wrapper_ptr node_create()
{
    node_wrapper_ptr node = NEW(node_wrapper);
    node->parent = NULL;
    node->type = UNKNOWN;
    node->node = NULL;
    return node;
}

static inline two_node_ptr two_node_create()
{
    two_node_ptr node = NEW(two_node);
    node->key = NULL;
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline three_node_ptr three_node_create()
{
    three_node_ptr node = NEW(three_node);
    node->left_key = NULL;
    node->left_value = NULL;
    node->right_key = NULL;
    node->right_value = NULL;
    node->left = NULL;
    node->middle = NULL;
    node->right = NULL;
    return node;
}

static inline void node_destroy(node_wrapper_ptr *node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }
    switch ((*node)->type)
    {
    case TWO_NODE:
    {
        two_node_destroy((two_node_ptr *)&(*node)->node);
        break;
    }

    case THREE_NODE:
    {
        three_node_destroy((three_node_ptr *)&(*node)->node);
        break;
    }
    default:
    {
        break;
    }
    }
}

static inline void two_node_destroy(two_node_ptr *node)
{
    if (node == NULL || *node == NULL)
    {
        return;
    }
    free((*node)->key);
    free((*node)->value);
    node_destroy(&(*node)->left);
    node_destroy(&(*node)->right);
    free(*node);
    *node = NULL;
}

static inline void three_node_destroy(three_node_ptr *node)
{
    if (node == NULL || *node == NULL)
    {
        return;
    }
    free((*node)->left_key);
    free((*node)->left_value);
    free((*node)->right_key);
    free((*node)->right_value);
    node_destroy(&(*node)->left);
    node_destroy(&(*node)->middle);
    node_destroy(&(*node)->right);
    free(*node);
    *node = NULL;
}

static inline void node_insert(node_wrapper_ptr node_wrapper, key_type key, value_type value, tt_compare compare)
{
    if (NULL == node_wrapper || NULL == key || NULL == compare)
    {
        return;
    }
    if (NULL == (node_wrapper)->node && UNKNOWN == (node_wrapper)->type)
    {
        two_node_ptr two_node = two_node_create();
        two_node->key = key;
        two_node->value = value;
        two_node->left = NULL;
        two_node->right = NULL;
        (node_wrapper)->type = TWO_NODE;
        (node_wrapper)->node = two_node;
        return;
    }
    else
    {
        insert(node_wrapper, key, value, compare);
    }
}

static inline void insert(node_wrapper_ptr node, key_type key, value_type value, tt_compare compare)
{
    if (NULL == node || NULL == key || NULL == compare)
    {
        return;
    }
    node_wrapper_ptr parent = NULL;
    node_wrapper_ptr position = node;
    while (NULL != position)
    {
        parent = position;
        switch ((position)->type)
        {
        case TWO_NODE:
        {
            two_node_ptr two_node = (two_node_ptr)((position)->node);
            int compare_result = compare(key, two_node->key);
            if (compare_result < 0)
            {
                position = (two_node->left);
            }
            else if (compare_result > 0)
            {
                position = (two_node->right);
            }
            else
            {
                two_node->value = value;
                return;
            }
            break;
        }
        case THREE_NODE:
        {
            three_node_ptr three_node = (three_node_ptr)((position)->node);
            int left_compare_result = compare(key, three_node->left_key);
            if (left_compare_result < 0)
            {
                position = (three_node->left);
            }
            else if (left_compare_result > 0)
            {
                int right_compare_result = compare(key, three_node->right_key);
                if (right_compare_result < 0)
                {
                    position = (three_node->middle);
                }
                else if (right_compare_result > 0)
                {
                    position = (three_node->right);
                }
                else
                {
                    three_node->right_value = value;
                    return;
                }
            }
            else
            {
                three_node->left_value = value;
                return;
            }
        }
        break;
        }
    }
    if (NULL == parent)
    {
        return;
    }
    switch ((parent)->type)
    {
    case TWO_NODE:
    {
        insert_into_two_node(parent, key, value, NULL, NULL, compare);
        break;
    }
    case THREE_NODE:
    {
        insert_into_three_node(parent, key, value, NULL, NULL, compare);
        break;
    }
    }
}

static inline void insert_into_two_node(node_wrapper_ptr node, key_type key, value_type value, node_wrapper_ptr left, node_wrapper_ptr right, tt_compare compare)
{
    printf("insert into two node, and key is: %s, value is %s\n", key, value);
    if (NULL == node || NULL == key || NULL == compare || (node)->type != TWO_NODE)
    {
        return;
    }
    two_node_ptr two_node = (two_node_ptr)((node)->node);
    int compare_result = compare(key, two_node->key);
    if (compare_result < 0)
    {
        three_node_ptr three_node = three_node_create();
        three_node->left_key = key;
        three_node->left_value = value;
        three_node->right_key = two_node->key;
        three_node->right_value = two_node->value;

        three_node->left = (left);
        three_node->middle = (right);
        three_node->right = two_node->right;

        (node)->node = three_node;
        (node)->type = THREE_NODE;
        free(two_node);
    }
    else if (compare_result > 0)
    {
        three_node_ptr three_node = three_node_create();
        three_node->left_key = two_node->key;
        three_node->left_value = two_node->value;
        three_node->right_key = key;
        three_node->right_value = value;

        three_node->left = two_node->left;
        three_node->middle = (left);
        three_node->right = (right);

        (node)->node = three_node;
        (node)->type = THREE_NODE;
        free(two_node);
    }
    else
    {
        two_node->value = value;
        return;
    }
}

static inline void insert_into_three_node(node_wrapper_ptr node, key_type key, value_type value, node_wrapper_ptr left, node_wrapper_ptr right, tt_compare compare)
{
    if (NULL == node || NULL == key || NULL == compare || node->type != THREE_NODE)
    {
        return;
    }
    three_node_ptr three_node = (three_node_ptr)((node)->node);
    int left_compare_result = compare(key, three_node->left_key);

    key_type root_key = NULL;
    value_type root_value = NULL;

    node_wrapper_ptr sub_left = NULL;
    node_wrapper_ptr sub_right = NULL;

    if (left_compare_result < 0)
    {
        root_key = three_node->left_key;
        root_value = three_node->left_value;

        two_node_ptr left_node = two_node_create();
        left_node->key = key;
        left_node->value = value;
        left_node->left = left;
        left_node->right = right;

        sub_left = node_create();
        sub_left->node = left_node;
        sub_left->type = TWO_NODE;

        two_node_ptr right_node = two_node_create();
        right_node->key = three_node->right_key;
        right_node->value = three_node->right_value;
        right_node->left = three_node->middle;
        right_node->right = three_node->right;

        sub_right = node_create();
        sub_right->node = right_node;
        sub_right->type = TWO_NODE;
    }
    else if (left_compare_result > 0)
    {
        int right_compare_result = compare(key, three_node->right_key);
        if (right_compare_result < 0)
        {
            root_key = key;
            root_value = value;

            two_node_ptr left_node = two_node_create();
            left_node->key = three_node->left_key;
            left_node->value = three_node->left_value;
            left_node->left = three_node->left;
            left_node->right = left;

            sub_left = node_create();
            sub_left->node = left_node;
            sub_left->type = TWO_NODE;

            two_node_ptr right_node = two_node_create();
            right_node->key = three_node->right_key;
            right_node->value = three_node->right_value;
            right_node->left = right;
            right_node->right = three_node->right;

            sub_right = node_create();
            sub_right->node = right_node;
            sub_right->type = TWO_NODE;
        }
        else if (right_compare_result > 0)
        {
            root_key = three_node->right_key;
            root_value = three_node->right_value;

            two_node_ptr left_node = two_node_create();
            left_node->key = three_node->left_key;
            left_node->value = three_node->left_value;
            left_node->left = three_node->left;
            left_node->right = three_node->middle;

            sub_left = node_create();
            sub_left->node = left_node;
            sub_left->type = TWO_NODE;

            two_node_ptr right_node = two_node_create();
            right_node->key = key;
            right_node->value = value;
            right_node->left = left;
            right_node->right = right;

            sub_right = node_create();
            sub_right->node = right_node;
            sub_right->type = TWO_NODE;
        }
        else
        {
            three_node->right_value = value;
            return;
        }
    }
    else
    {
        three_node->left_value = value;
        return;
    }
    if (NULL == (node)->parent)
    {
        two_node_ptr root = two_node_create();
        root->key = root_key;
        root->value = root_value;

        root->left = sub_left;
        root->right = sub_right;
        set_parent(sub_left, node);
        set_parent(sub_right, node);

        (node)->node = root;
        (node)->type = TWO_NODE;
        free(three_node);
    }
    else
    {
        set_parent(sub_left, node->parent);
        set_parent(sub_right, node->parent);
        node_wrapper_ptr parent = (node)->parent;
        switch (parent->type)
        {
        case TWO_NODE:
        {
            insert_into_two_node((node)->parent, root_key, root_value, sub_left, sub_right, compare);
            break;
        }
        case THREE_NODE:
        {
            insert_into_three_node((node)->parent, root_key, root_value, sub_left, sub_right, compare);
            break;
        }
        }
    }
}

static inline void set_parent(node_wrapper_ptr node, node_wrapper_ptr parent)
{
    if (NULL == node)
    {
        return;
    }
    node->parent = parent;
}

extern tt_tree_entry_ptr tt_tree_create(tt_compare compare, key_cpy kconvert, value_cpy vconvert)
{
    tt_tree_entry_ptr entry = NEW(tt_tree_entry);
    entry->root = NULL;
    entry->compare = compare;
    entry->kconvert = kconvert;
    entry->vconvert = vconvert;
    return entry;
}
extern void tt_tree_destroy(tt_tree_entry_ptr *entry)
{
    if (entry == NULL || *entry == NULL)
    {
        return;
    }
    if (NULL != (*entry)->root)
    {
        node_destroy((node_wrapper_ptr *)&(*entry)->root);
    }

    free(*entry);
    *entry = NULL;
}
extern void tt_tree_insert(tt_tree_entry_ptr entry, tt_key_type key, tt_value_type value)
{
    if (NULL == entry || NULL == key || NULL == entry->compare)
    {
        return;
    }

    if (NULL == entry->root)
    {
        node_wrapper_ptr wrapper = node_create();
        entry->root = wrapper;
    }
    key_type key_cpy = entry->kconvert(key);
    value_type value_cpy = entry->vconvert(value);
    node_insert((node_wrapper_ptr)(entry->root), key_cpy, value_cpy, entry->compare);
}
extern tt_value_type tt_tree_search(tt_tree_entry_ptr entry, tt_key_type key)
{
    if (NULL == entry || NULL == entry->root || NULL == key || NULL == entry->compare)
    {
        return NULL;
    }
    printf("serch for %s\n", key);
    node_wrapper_ptr position = (node_wrapper_ptr)(entry->root);
    while (position != NULL)
    {
        switch (position->type)
        {
        case TWO_NODE:
        {
            two_node_ptr two_node = (two_node_ptr)(position->node);
            int compare_result = entry->compare(key, two_node->key);
            printf("compare with two node key: %s, and compare result is %d\n", two_node->key, compare_result);
            if (compare_result < 0)
            {
                position = two_node->left;
            }
            else if (compare_result > 0)
            {
                position = two_node->right;
            }
            else
            {
                return two_node->value;
            }
            continue;
        }
        case THREE_NODE:
        {
            three_node_ptr three_node = (three_node_ptr)(position->node);
            int left_compare_result = entry->compare(key, three_node->left_key);
            printf("compare with three node left key: %s, and left compare result is %d\n", three_node->left_key, left_compare_result);
            if (left_compare_result < 0)
            {
                position = three_node->left;
            }
            else if (left_compare_result > 0)
            {
                int right_compare_result = entry->compare(key, three_node->right_key);
                printf("compare with three node right key: %s, and right compare result is %d\n", three_node->right_key, right_compare_result);
                if (right_compare_result < 0)
                {
                    position = three_node->middle;
                }
                else if (right_compare_result > 0)
                {
                    position = three_node->right;
                }
                else
                {
                    return three_node->right_value;
                }
            }
            else
            {
                return three_node->left_value;
            }
            continue;
            ;
        }
        }
        return NULL;
    }
}
extern void tt_tree_delete(tt_tree_entry_ptr entry, tt_key_type key)
{
    // todo: this part is too dificult, so I will do it later.
}

#ifdef _TEST_
#include <string.h>
static inline key_type key_cpy(tt_key_type key)
{
    if (NULL == key)
    {
        return NULL;
    }
    return strcpy(malloc_with_check(strlen(key) + 1), key);
}

static inline value_type value_cpy(tt_value_type value)
{
    if (NULL == value)
    {
        return NULL;
    }
    return strcpy(malloc_with_check(strlen(value) + 1), value);
}

extern void tt_tree_test(void)
{
    tt_tree_entry_ptr entry = tt_tree_create(strcmp, key_cpy, value_cpy);
    tt_tree_insert(entry, "key2", "value2");
    tt_tree_insert(entry, "key3", "value3");
    tt_tree_insert(entry, "key5", "value5");
    tt_tree_insert(entry, "key", "value");
    tt_tree_insert(entry, "key1", "value1");
    tt_tree_insert(entry, "key4", "value4");

    tt_value_type result = tt_tree_search(entry, "key");
    printf("result: %s\n\n", result);

    result = tt_tree_search(entry, "key1");
    printf("result: %s\n\n", result);

    result = tt_tree_search(entry, "key2");
    printf("result: %s\n\n", result);

    result = tt_tree_search(entry, "key3");
    printf("result: %s\n\n", result);

    result = tt_tree_search(entry, "key4");
    printf("result: %s\n\n", result);

    result = tt_tree_search(entry, "key5");
    printf("result: %s\n\n", result);

    tt_tree_destroy(&entry);
}
#endif