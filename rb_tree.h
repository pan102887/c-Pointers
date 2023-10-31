#ifndef _RB_TREE_H_
#define _RB_TREE_H_

typedef struct rb_entry
{
    void *root;
} rb_entry;

typedef struct rb_entry *rb_tree;


#ifdef _TEST_
extern void rb_tree_test();
#endif
#endif