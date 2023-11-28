#ifndef _RB_TREE_H_
#define _RB_TREE_H_

/**
 * @brief Red-black tree —— 红黑树
 * 红黑树：含有红黑链接，并满足以下条件的二叉查找树：
 *      - 红链接均为左链接
 *      - 没有任何一个节点同时和两个红链接相连接；
 *      - 树是完美的黑链接平衡，即任意空连接到根节点的路径上的黑链接数量相同
 */
typedef const char *rb_key_type;
typedef const char *rb_value_type;
typedef char *rb_internal_key_type;
typedef char *rb_internal_value_type;

typedef int (*key_compare_f)(rb_key_type, rb_key_type);
typedef rb_internal_key_type (*rb_key_cpy_f)(rb_key_type);
typedef rb_internal_value_type (*rb_value_cpy_f)(rb_value_type);
typedef void (*rb_desctroy_f)(rb_internal_key_type *, rb_internal_value_type *);

typedef struct rb_entry
{
    void *root;
    rb_key_cpy_f kcpy;
    rb_value_cpy_f vcpy;
    key_compare_f compare;
    rb_desctroy_f destroy;
} rb_entry;
typedef struct rb_entry *rb_tree_ptr;

#ifdef cplusplus
extern "C" {
#endif

extern rb_tree_ptr rb_tree_create(key_compare_f compare, rb_key_cpy_f kcpy, rb_value_cpy_f vcpy, rb_desctroy_f destroy);
extern void rb_tree_destroy(rb_tree_ptr *entry);
extern void rb_tree_insert(rb_tree_ptr entry, rb_key_type key, rb_value_type value);
extern rb_value_type rb_tree_search(rb_tree_ptr entry, rb_key_type key);
extern void rb_tree_delete(rb_tree_ptr entry, rb_key_type key);

#ifdef cplusplus
}
#endif

#ifdef _TEST_
extern void rb_tree_test();
#endif
#endif