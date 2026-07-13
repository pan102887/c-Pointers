#ifndef CP_COMMON_TWO_THREE_SEARCH_TREE_H
#define CP_COMMON_TWO_THREE_SEARCH_TREE_H

typedef struct two_three_search_tree_node {
    int key1;
    int key2;
    int key3;
    struct two_three_search_tree_node *left;
    struct two_three_search_tree_node *middle;
    struct two_three_search_tree_node *right;
} two_three_search_tree_node;

#endif