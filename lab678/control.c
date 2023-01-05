#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <zmq.h>
#include <log.h>

#include "map.h"
#include "tree.h"


int main() {
    log_info("control node started");

    node *root = NULL;

    while (1) {
        char command[100];
        scanf("%s", command);

        if (strcmp(command, "create") == 0) { 
            // create id
            
            char id[10];
            scanf("%s", id);
            node *new_node;
            node_init(&new_node, atoi(id));
            int can = 0;
            if (root == NULL) {
                can = 1;
                root = new_node;
            } else {
                if (node_find(atoi(id), root) != NULL) {
                    printf("error: already exists\n");
                } else {
                    can = 1;
                    node_insert(new_node, root);
                }
            }
            if (can) {
                int pid = fork();
                
                if (pid == 0) {
                    printf("ok: %d\n", getpid());
                    execl("./build/comput", "./build/comput", id, NULL);
                }
            }
        } else if (strcmp(command, "remove") == 0) {
            // remove id

            int id;
            scanf("%d", id);
            node *res_node = node_find(id, root);
            if (res_node == NULL) {
                printf("error: not found\n");
            }
        }

        node_print_tree(root, 0);

    }
}