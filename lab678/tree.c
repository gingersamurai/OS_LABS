#include "tree.h"
#include <log.h>

void node_init(node **cur_node, int id) {
    *cur_node = (node *) malloc(sizeof(node));
    
    (*cur_node)->id = id;
    (*cur_node)->left_child = NULL;
    (*cur_node)->right_child = NULL;
    (*cur_node)->parent = NULL;
}

void node_insert(node *cur_node, node *root) {
    if (cur_node->id <= root->id) {
        
        if (root->left_child != NULL) {
            node_insert(cur_node, root->left_child);
        } else {
            root->left_child = cur_node;
            cur_node->parent = root;
        }
    } else {
        if (root->right_child != NULL) {
            node_insert(cur_node, root->right_child);
        } else {
            root->right_child = cur_node;
            cur_node->parent = root;
        }
    }
}


void node_print_tree(node *root, int depth) {
    if (root == NULL) return;
    node_print_tree(root->right_child, depth + 1);
    for (int i = 0; i < depth; i++) printf("\t");
    printf("%d\n\n", root->id);
    node_print_tree(root->left_child, depth + 1);
}


node * node_find(int need_id, node *root) {
    if (root == NULL) return NULL;
    if (need_id == root->id) {
        return root;
    } else if (need_id < root->id) {
        return node_find(need_id, root->left_child);
    } else {
        return node_find(need_id, root->right_child);
    }
    
}

void node_delete(node **cur_node) {
    // root
    if ((*cur_node)->parent == NULL) {
        *cur_node = NULL;
        return;
    }

    // leave
    if ( (*cur_node)->left_child == NULL && (*cur_node)->right_child == NULL) {
        node *cur_parent = (*cur_node)->parent;
        int is_left_child = 0;
        if (cur_parent->left_child == *cur_node) {
            is_left_child = 1;
        }
        free(*cur_node);

        if (is_left_child) {
            cur_parent->left_child = NULL;
        } else {
            cur_parent->right_child = NULL;
        }

    // only left son
    } else if ((*cur_node)->left_child != NULL && (*cur_node)->right_child == NULL) {
        node *cur_parent = (*cur_node)->parent;
        node *cur_left_child = (*cur_node)->left_child;

        int is_left_child = 0;
        if (cur_parent->left_child == *cur_node) {
            is_left_child = 1;
        }
        free(*cur_node);

        if (is_left_child) {
            cur_parent->left_child = cur_left_child;
            cur_left_child->parent = cur_parent;
        } else {
            cur_parent->right_child = cur_left_child;
            cur_left_child->parent = cur_parent;
        }
    // only right son
    } else if ((*cur_node)->left_child == NULL && (*cur_node)->right_child != NULL) {
        node *cur_parent = (*cur_node)->parent;
        node *cur_right_child = (*cur_node)->right_child;
        
        int is_left_child = 0;
        if (cur_parent->left_child == *cur_node) {
            is_left_child = 1;
        }
        free(*cur_node);

        if (is_left_child) {
            cur_parent->left_child = cur_right_child;
            cur_right_child->parent = cur_parent;
        } else {
            cur_parent->right_child = cur_right_child;
            cur_right_child->parent = cur_parent;
        }
    // both sons
    } else {
        node *min_node = (*cur_node)->right_child;
        while (min_node->left_child != NULL) min_node = min_node->left_child;
        (*cur_node)->id = min_node->id;
        node_delete(&min_node);
    }
}


// int main() {
//     node *root = NULL;
//     while (1) {
//         printf("add new: 1 id\n");
//         printf("print: 2\n");
//         printf("find: 3 id\n");
//         printf("delete: 4 id\n");
//         printf("input: ");
//         int req;
//         scanf("%d", &req);
//         if (req == 1) {
//             int id;
//             scanf("%d", &id);
//             node *new_node;
//             node_init(&new_node, id);
//             if (root == NULL) {
//                 root = new_node;
//             } else {
//                 node_insert(new_node, root);
//             }
//             printf("added\n");
//         } else if (req == 2) {
//             node_print_tree(root, 0);
//         } else if (req == 3) {
//             int id;
//             scanf("%d", &id);
//             node *res_node = node_find(id, root);
//             if (res_node == NULL) {
//                 printf("not found\n");
//             } else {
//                 printf("found\n");
//             }
//         } else if (req == 4) {
//             int id;
//             scanf("%d", &id);
//             node *res_node = node_find(id, root);
//             if (res_node == NULL) {
//                 printf("not found\n");
//             } else {
//                 node_delete(&res_node);
//                 printf("deleted\n");
//             }
//         }
//         printf("\n");
//     }
// }
