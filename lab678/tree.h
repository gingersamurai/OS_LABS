#ifndef TREE
#define TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    int id;
    struct _node *left_child;
    struct _node *right_child;
    struct _node *parent;
} node;

void node_init(node **cur_node, int id);

void node_insert(node *cur_node, node *root);

void node_print_tree(node *root, int depth);

node *node_find(int need_id, node *root);

void  node_delete(node **cur_node);

#endif