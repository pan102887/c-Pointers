#ifndef _TT_TREE_H_
#define _TT_TREE_H_
#include <stddef.h>
/**
 * @brief 23查找树
 * 有两种节点，2节点与3节点，2节点可有一个value以及两个子节点，left和right。3节点有两个value，并且可以有3个子节点，left, midle和right。
 * 当
 * 
 */

typedef struct
{
    void *root;

} tt_tree_entry;

typedef char *tt_key_t;
typedef char *value_t;

extern tt_tree_entry *tt_tree_create(void);
extern void tt_tree_destroy(tt_tree_entry *tree);

extern void tt_tree_insert(tt_tree_entry *tree, tt_key_t key, value_t value, int (*compare)(value_t, value_t));
extern void tt_tree_delete(tt_tree_entry *tree, tt_key_t key);
extern value_t tt_tree_search(tt_tree_entry *tree, tt_key_t key);


/**
 * ======================== ▀█▀ ██▀ ▄▀▀ ▀█▀  ========================
 * ========================  █  █▄▄ ▄█▀  █   ========================
 */
#ifdef _TEST_
extern void tt_tree_test(void);
#endif

#endif