#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <zmq.h>
#include <log.h>

#include "map.h"
#include "tree.h"

void send_message(char *text, int id, char *reply) {
    void *context = zmq_ctx_new();
    void *request_socket = zmq_socket(context, ZMQ_REQ);  
    char adress[100];
    sprintf(adress, "tcp://localhost:%d", 10000 + id);
    zmq_connect(request_socket, adress);
    log_trace("connected to %s", adress);

    zmq_msg_t req_msg;
    zmq_msg_init_size(&req_msg, strlen(text) + 1);
    memcpy(zmq_msg_data(&req_msg), text, strlen(text) + 1);
    log_trace("sending message: %s", (char *)zmq_msg_data(&req_msg));
    zmq_msg_send(&req_msg, request_socket, 0);
    log_trace("message send");
    zmq_msg_close(&req_msg);


    zmq_msg_t rep_msg;
    zmq_msg_init(&rep_msg);
    log_trace("receiving mesage");
    zmq_msg_recv(&rep_msg, request_socket, 0);
    log_trace("message received: %s", (char *)zmq_msg_data(&rep_msg));
    memcpy(reply, zmq_msg_data(&rep_msg), zmq_msg_size(&rep_msg));
    zmq_msg_close(&req_msg);

    zmq_close(request_socket);
    zmq_ctx_destroy(context); 
}

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
            scanf("%d", &id);
            node *res_node = node_find(id, root);
            if (res_node == NULL) {
                printf("error: not found\n");
            } else {
                node_delete(&res_node);
                printf("ok\n");
                char ans[100];
                log_trace("sending message");
                send_message("remove", id, ans);
            }
        } else if (strcmp(command, "exec") == 0) {
            // exec id key val
            int id;
            scanf("%d", &id);
            char buff[100];
            fgets(buff, 100, stdin);
            char message[1000];
            sprintf(message, "exec %s", buff);
            message[strlen(message)-1] = '\0';
            char ans[1000];
            send_message(message, id, ans);
            printf("%s\n",ans);
        }

        // node_print_tree(root, 0);

    }
}