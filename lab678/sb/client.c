#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <log.h>

int main (void) {
    log_info("client started");

    void *context = zmq_ctx_new();
    void* request = zmq_socket(context, ZMQ_REQ); 
    zmq_connect(request, "tcp://localhost:4040");
    
    int count = 0;

    while (1) {
        zmq_msg_t req;
        zmq_msg_init_size(&req, strlen("hello\0")+1);
        memcpy(zmq_msg_data(&req), "hello\0", strlen("hello\0")+1);
        log_trace("send: %s size: %d count: %d", (char *)zmq_msg_data(&req), zmq_msg_size(&req), count);
        zmq_msg_send(&req, request, 0);
        zmq_msg_close(&req);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, request, 0); 
        log_trace("receiced: %s size: %d count: %d\n", (char *)zmq_msg_data(&reply), zmq_msg_size(&reply), count++);
        zmq_msg_close(&reply);
    }

    zmq_close(request);
    zmq_ctx_destroy(context);
}