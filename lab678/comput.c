#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <zmq.h>
#include <log.h>

#include "map.h"
#include "tree.h"
 
int main(int argc, const char **argv) {
    int id = atoi(argv[1]);
    log_info("comput node with id = %d started", id);

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
        log_trace("message received");
        char request[100];
        memcpy(request, zmq_msg_data(&req_msg), zmq_msg_size(&req_msg));
        printf("id: %d  received %s\n", id, request);
        zmq_msg_close(&req_msg);

        char text[100] = "ok";
        zmq_msg_t rep_msg;
        zmq_msg_init_size(&rep_msg, strlen(text)+1);
        memcpy(zmq_msg_data(&rep_msg), text, strlen(text)+1);
        log_trace("sending message");
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