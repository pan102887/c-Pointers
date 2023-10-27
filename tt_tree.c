#include "tt_tree.h"

#include "m_def.h"

#include <stdio.h>
#include <stdlib.h>

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

typedef char *key_type;
typedef char *value_type;

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
static inline void node_insert(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type));
static inline void insert(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type));
static inline void insert_into_two_node(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type));
static inline void insert_into_three_node(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type));

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

static inline void node_insert(node_wrapper_ptr *node_wrapper, key_type key, value_type value, int (*compare)(key_type, key_type))
{
    if (NULL == node_wrapper  || NULL == *node_wrapper || NULL == key || NULL == compare)
    {
        return;
    }
    if (NULL == (*node_wrapper)->node && UNKNOWN == (*node_wrapper)->type)
    {
        two_node_ptr two_node = two_node_create();
        two_node->key = key;
        two_node->value = value;
        two_node->left = NULL;
        two_node->right = NULL;
        (*node_wrapper)->type = TWO_NODE;
        (*node_wrapper)->node = two_node;
        return;
    }
    else
    {
        insert(node_wrapper, key, value, compare);
    }
}

static inline void insert(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type))
{
    if (NULL == node || NULL == *node || NULL == key || NULL == compare)
    {
        return;
    }
    node_wrapper_ptr *parent = NULL;
    node_wrapper_ptr *position = node;
    while (NULL != *position)
    {
        parent = position;
        switch ((*position)->type)
        {
        case TWO_NODE:
        {
            two_node_ptr two_node = (two_node_ptr)((*position)->node);
            int compare_result = compare(key, two_node->key);
            if (compare_result < 0)
            {
                position = &(two_node->left);
            }
            else if (compare_result > 0)
            {
                position = &(two_node->right);
            }
            else
            {
                two_node->value = value;
                return;
            }
        }
        case THREE_NODE:
        {
            three_node_ptr three_node = (three_node_ptr)((*position)->node);
            int left_compare_result = compare(key, three_node->left_key);
            if (left_compare_result < 0)
            {
                position = &(three_node->left);
            }
            else if (left_compare_result > 0)
            {
                int right_compare_result = compare(key, three_node->right_key);
                if (right_compare_result < 0)
                {
                    position = &(three_node->middle);
                }
                else if (right_compare_result > 0)
                {
                    position = &(three_node->right);
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
        }
    }
    if (NULL == *parent)
    {
        return;
    }
    switch ((*parent)->type)
    {
    case TWO_NODE:
    {
        insert_into_two_node(parent, key, value, compare);
    }
    case THREE_NODE:
    {
        insert_into_three_node(parent, key, value, compare);
    }
    }

}

static inline void insert_into_two_node(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type))
{
    if (NULL == node || NULL == *node || NULL == key || NULL == compare || (*node)->type != TWO_NODE)
    {
        return;
    }
    two_node_ptr two_node = (two_node_ptr)((*node)->node);
    int compare_result = compare(key, two_node->key);
    if (compare_result < 0)
    {
        three_node_ptr three_node = three_node_create();
        three_node->left_key = key;
        three_node->left_value = value;
        three_node->right_key = two_node->key;
        three_node->right_value = two_node->value;

        three_node->left = NULL;
        three_node->middle = two_node->left;
        three_node->right = two_node->right;

        (*node)->node = three_node;
        (*node)->type = THREE_NODE;
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
        three_node->middle = two_node->right;
        three_node->right = NULL;

        (*node)->node = three_node;
        (*node)->type = THREE_NODE;
        free(two_node);
    }
    else
    {
        two_node->value = value;
    }
}

static inline void insert_into_three_node(node_wrapper_ptr *node, key_type key, value_type value, int (*compare)(key_type, key_type))
{
    if (NULL == node || NULL == *node || NULL == key || NULL == compare || (*node)->type != THREE_NODE)
    {
        return;
    }
    three_node_ptr three_node = (three_node_ptr)((*node)->node);
    int left_compare_result = compare(key, three_node->left_key);
    int right_compare_result = compare(key, three_node->right_key);

    key_type root_key = NULL;
    value_type root_value = NULL;

    node_wrapper_ptr left = NULL;
    node_wrapper_ptr right = NULL;

    if (left_compare_result < 0)
    {
        root_key = three_node->left_key;
        root_value = three_node->left_value;

        two_node_ptr left_node = two_node_create();
        left_node->key = key;
        left_node->value = value;
        left_node->left = NULL;
        left_node->right = three_node->left;
        left = node_create();
        left->node = left_node;
        left->type = TWO_NODE;

        two_node_ptr right_node = two_node_create();
        right_node->key = three_node->right_key;
        right_node->value = three_node->right_value;
        right_node->left = three_node->middle;
        right_node->right = three_node->right;
        right = node_create();
        right->node = right_node;
        right->type = TWO_NODE;
    }
    else if (left_compare_result > 0)
    {
        if (right_compare_result < 0)
        {
            root_key = key;
            root_value = value;

            two_node_ptr left_node = two_node_create();
            left_node->key = three_node->left_key;
            left_node->value = three_node->left_value;
            left_node->left = three_node->left;
            left_node->right = three_node->middle;
            left = node_create();
            left->node = left_node;
            left->type = TWO_NODE;

            two_node_ptr right_node = two_node_create();
            right_node->key = three_node->right_key;
            right_node->value = three_node->right_value;
            right_node->left = NULL;
            right_node->right = three_node->right;
            right = node_create();
            right->node = right_node;
            right->type = TWO_NODE;
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
            left = node_create();
            left->node = left_node;
            left->type = TWO_NODE;

            two_node_ptr right_node = two_node_create();
            right_node->key = key;
            right_node->value = value;
            right_node->left = three_node->right;
            right_node->right = NULL;
            right = node_create();
            right->node = right_node;
            right->type = TWO_NODE;
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
    if (NULL == (*node)->parent)
    {
        two_node_ptr root = two_node_create();
        root->key = root_key;
        root->value = root_value;
        root->left = left;
        root->right = right;
        (*node)->node = root;
        (*node)->type = TWO_NODE;
        free(three_node);
    }
    else
    {
        node_wrapper_ptr parent = (*node)->parent;
        switch (parent->type)
        {
        case TWO_NODE:
        {
            insert_into_two_node(&parent, root_key, root_value, compare);
            break;
        }
        case THREE_NODE:
        {
            insert_into_three_node(&parent, root_key, root_value, compare);
            break;
        }
        }
    
    }
}



extern tt_tree_entry_ptr tt_tree_create(int (*compare)(tt_key_type, tt_key_type))
{
    tt_tree_entry_ptr entry = NEW(tt_tree_entry);
    entry->root = NULL;
    entry->compare = compare;
    return entry;
}
extern void tt_tree_destroy(tt_tree_entry_ptr *entry)
{
    if (entry == NULL || *entry == NULL)
    {
        return;
    }
    node_destroy((node_wrapper_ptr *)&(*entry)->root);
    free(*entry);
    *entry = NULL;
}
extern void tt_tree_insert(tt_tree_entry_ptr entry, tt_key_type key, tt_value_type value)
{
    if (NULL == entry || NULL == key)
    {
        return;
    }
    if (NULL == entry->compare)
    {
        return;
    }

    if (NULL == entry->root)
    {
        node_wrapper_ptr wrapper = node_create();
        entry->root = wrapper;
    }
    node_insert(&(entry->root), key, value, entry->compare);
}
extern tt_value_type tt_tree_search(tt_tree_entry_ptr entry, tt_key_type key);
extern void tt_tree_delete(tt_tree_entry_ptr entry, tt_key_type key);

#ifdef _TEST_
extern void tt_tree_test(void)
{
    printf("tt tree test\n");
    printf("sizeof node type: %ld\n", sizeof(node_type));
}
#endif