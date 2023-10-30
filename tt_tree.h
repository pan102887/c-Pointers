#ifndef _TT_TREE_H_
#define _TT_TREE_H_

typedef char* tt_key_type;
typedef char* tt_value_type;

typedef char *key_type;
typedef char *value_type;

typedef struct tt_tree_entry
{
    void *root;
    int (*compare)(tt_key_type, tt_key_type);
} tt_tree_entry;

typedef tt_tree_entry* tt_tree_entry_ptr;

extern tt_tree_entry_ptr tt_tree_create(int (*compare)(tt_key_type, tt_key_type));
extern void tt_tree_destroy(tt_tree_entry_ptr *entry);
extern void tt_tree_insert(tt_tree_entry_ptr entry, tt_key_type key, tt_value_type value);
extern tt_value_type tt_tree_search(tt_tree_entry_ptr entry, tt_key_type key);
extern void tt_tree_delete(tt_tree_entry_ptr entry, tt_key_type key);

/**
 * ======================== ▀█▀ ██▀ ▄▀▀ ▀█▀  ========================
 * ========================  █  █▄▄ ▄█▀  █   ========================
 */
#ifdef _TEST_
extern void tt_tree_test(void);
#endif

#endif