#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <zmq.h>
#include <log.h>

#include "map.h"
#include "tree.h"

void ans_exec(char *request, char *result, map *my_map, int id) {
    char *pch = strtok(request, " ");
    pch = strtok(NULL, " ");
    char *wkey = pch;
    char *key = malloc(100);
    strcpy(key, wkey);
    pch = strtok(NULL, " ");
    if (pch == NULL) {
        log_warn("key: [%s]", key);
        int pos = map_find(key, *my_map);
        
        if (pos == -1) {
           sprintf(result, "ok:%d: \'%s\' not found", id, key); 
        } else {
            sprintf(result, "ok:%d %d", id, (my_map->array)[pos].value);
        }
    } else {
        int val = atoi(pch);
        log_warn("key: [%s]  value: [%d]", key, val);
        map_insert(key, val, my_map);
        sprintf(result, "ok:%d", id);
    }    
}

int main(int argc, const char **argv) {
    int id = atoi(argv[1]);
    log_info("comput node with id = %d started", id);

    map my_map;
    map_init(&my_map);

    void* context = zmq_ctx_new();
	void* respond_socket = zmq_socket(context, ZMQ_REP);

    char adress[100];
    sprintf(adress, "tcp://*:%d", 10000 + id);
    zmq_bind(respond_socket, adress);
    log_trace("binded to %s", adress);

    while (1) {
        zmq_msg_t req_msg;
        zmq_msg_init(&req_msg);
        log_trace("receiving message");
        zmq_msg_recv(&req_msg, respond_socket, 0);
        log_trace("message received: %s", (char *)zmq_msg_data(&req_msg));
        char request[100];
        memcpy(request, zmq_msg_data(&req_msg), zmq_msg_size(&req_msg));
        zmq_msg_close(&req_msg);
        
        char text[100];
        sprintf(text, "ok:%d", id);
        if (strstr(request, "exec") - request == 0) {
            
            ans_exec(request, text, &my_map, id);
        }
        
        zmq_msg_t rep_msg;
        zmq_msg_init_size(&rep_msg, strlen(text)+1);
        memcpy(zmq_msg_data(&rep_msg), text, strlen(text)+1);
        log_trace("sending message: %s", (char *)zmq_msg_data(&rep_msg));
        zmq_msg_send(&rep_msg, respond_socket, 0);
        log_trace("message send");
        zmq_msg_close(&rep_msg);

        if (strcmp(request, "remove") == 0) {
            zmq_close(respond_socket);
	        zmq_ctx_destroy(context);
            log_info("comput node with id = %d finished", id);
            exit(0);
        }
    }
}