#include "b_tree.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct b_tree_node_stack
{
    b_tree_node *node;
    struct b_tree_node_stack *next;
} b_tree_node_stack;
typedef enum node_stack_push_result
{
    PUSH_SUCCESS,
    PUSH_FAILURE
} node_stack_push_result;

static inline b_tree_node *node_stack_pop(b_tree_node_stack **stack);
static inline node_stack_push_result node_stack_push(b_tree_node_stack **stack, b_tree_node *node);
static inline void node_stack_free(b_tree_node_stack **stack);

static inline void node_height_adjust(b_tree_node_stack **stack);

static inline size_t b_tree_node_height(b_tree_node *node);
static inline b_tree_node *alloc_b_tree_node(int key, void *value);
static inline void b_tree_node_insert(b_tree_node **root, int key, void *value);
static inline void b_tree_subtree_free(b_tree_node **root);
static inline void b_tree_node_delete(b_tree_node **root, int key);
static inline void b_tree_node_free(b_tree_node **node, b_tree_node_stack **stack);
static inline void b_tree_node_print(b_tree_node *tree);

static inline b_tree_node *node_stack_pop(b_tree_node_stack **stack)
{
    if (NULL == stack || NULL == *stack)
    {
        return NULL;
    }
    b_tree_node_stack *temp = *stack;
    *stack = (*stack)->next;
    b_tree_node *node = temp->node;
    free(temp);
}

static inline node_stack_push_result node_stack_push(b_tree_node_stack **stack, b_tree_node *node)
{
    if (NULL == stack || NULL == node)
    {
        return PUSH_FAILURE;
    }
    b_tree_node_stack *new_node = malloc(sizeof(b_tree_node_stack));
    if (NULL == new_node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->node = node;
    new_node->next = *stack;
    *stack = new_node;
    return PUSH_SUCCESS;
}

static inline void node_stack_free(b_tree_node_stack **stack)
{
    if (NULL == stack || NULL == *stack)
    {
        return;
    }
    b_tree_node_stack *current = *stack;
    while (current != NULL)
    {
        b_tree_node_stack *temp = current;
        current = current->next;
        free(temp);
    }
    *stack = NULL;
}

static inline void node_height_adjust(b_tree_node_stack **stack)
{
    b_tree_node *currnt = NULL;
    while((currnt = node_stack_pop(stack)) != NULL)
    {
        size_t left_height = b_tree_node_height(currnt->left);
        size_t right_height = b_tree_node_height(currnt->right);
        currnt->height = MAX(left_height, right_height) + 1;
    }
}

static inline size_t b_tree_node_height(b_tree_node *node)
{
    if (NULL == node){
        return 0;
    }
    return node->height;
}

extern b_tree *b_tree_new()
{
    b_tree *tree = malloc(sizeof(b_tree));
    if (NULL == tree)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
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
    b_tree_node_stack *stack = NULL;
    b_tree_node **insert_position = root;
    while (*insert_position != NULL)
    {
        node_stack_push(&stack, *insert_position);
        if (key < (*insert_position)->key)
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
            node_stack_free(&stack);
            return;
        }
    }
    *insert_position = alloc_b_tree_node(key, value);
    node_height_adjust(&stack);
}

static inline b_tree_node *alloc_b_tree_node(int key, void *value)
{
    b_tree_node *node = malloc(sizeof(b_tree_node));
    if (NULL == node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->value = value;
    node->height = 1;
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
    b_tree_node_stack *stack = NULL;
    b_tree_node **delete_position = root;
    while (*delete_position != NULL)
    {
        b_tree_node *current = *delete_position;
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
        node_stack_push(&stack, current);
    }
    if (NULL == *delete_position)
    {
        node_stack_free(&stack);
        return;
    }
    b_tree_node_free(delete_position, &stack);
    node_height_adjust(&stack);
}

static inline void b_tree_node_free(b_tree_node **node, b_tree_node_stack **stack)
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
        b_tree_node **new_subtree_root = &((*node)->right);
        while ((*new_subtree_root)->left != NULL)
        {
            node_stack_push(stack, *new_subtree_root);
            new_subtree_root = &((*new_subtree_root)->left);
        }
        (*node)->key = (*new_subtree_root)->key;
        (*node)->value = (*new_subtree_root)->value;
        b_tree_node_free(new_subtree_root, stack);
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
static inline void node_display(b_tree_node *node);
static inline void search_and_print(b_tree *tree, int key)
{
    b_tree_node *node = b_tree_search(tree, key);
    node_display(node);
}

static inline void node_display(b_tree_node *node)
{
    if (NULL != node)
    {
        printf("find node with key %d and value is: \"%s\"\n", node->key, (char *)node->value);
    }
    else
    {
        printf("invalid pointer of node\n");
    }
}

static inline void test_one(void)
{
    b_tree *tree = b_tree_new();
    // root
    b_tree_insert(tree, 5, "5");

    // left
    b_tree_insert(tree, 2, "2");
    b_tree_insert(tree, 3, "3");
    b_tree_insert(tree, 1, "1");

    // right
    b_tree_insert(tree, 8, "8");
    b_tree_insert(tree, 6, "6");
    b_tree_insert(tree, 7, "7");
    b_tree_insert(tree, 9, "9");

    node_display(tree->root);
    b_tree_delete(tree, tree->root->key);
    node_display(tree->root);
}

static inline void test_two(void)
{
    b_tree *tree = b_tree_new();
    b_tree_insert(tree, 5, "5");
    b_tree_insert(tree, 3, "3");
    b_tree_insert(tree, 6, "6");
    b_tree_insert(tree, 7, "7");
    b_tree_insert(tree, 2, "2");
    b_tree_insert(tree, 4, "4");
    b_tree_insert(tree, 8, "8");
    b_tree_insert(tree, 10, "10");
    b_tree_insert(tree, 11, "11");
    b_tree_insert(tree, 1, "1");
    b_tree_insert(tree, 9, "9");

    search_and_print(tree, 2);
    b_tree_insert(tree, 2, "2 after change");
    search_and_print(tree, 2);

    search_and_print(tree, 12);
    b_tree_print(tree);

    b_tree_delete(tree, 5);
    search_and_print(tree, 6);
    search_and_print(tree, 7);
    b_tree_print(tree);

    b_tree_free(tree);
    b_tree_print(tree);
}

void b_tree_test()
{
    test_one();
    test_two();
}
#endif