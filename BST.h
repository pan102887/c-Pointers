#ifndef _BST_H_
#define _BST_H_

/**
 * @brief binary search tree node
 * 
 */
typedef struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
    struct BSTNode *parent;
    int height;
    int balance;
    int (*compare)(void *, void *);
    void (*print)(void *);
    void (*del)(void *);
    
}BSTNode;

#endif