#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <log.h>

int main (void) {
    log_info("server started\n");
    
    void *context = zmq_ctx_new();
    void* respond = zmq_socket(context, ZMQ_REP);
    zmq_bind(respond, "tcp://*:4040");
    

    while (1) {
        zmq_msg_t request;
        zmq_msg_init(&request);
        zmq_msg_recv(&request, respond, 0);
        log_trace("receiced: %s with size %d", (char *)zmq_msg_data(&request), zmq_msg_size(&request));
        zmq_msg_close(&request);
        
        sleep(1);

        zmq_msg_t reply;
        zmq_msg_init_size(&reply, strlen("world\0")+1);
        memcpy(zmq_msg_data(&reply), "world\0", strlen("world\0")+1);
        log_trace("send: %s with size: %d\n", (char *)zmq_msg_data(&reply), zmq_msg_size(&reply));
        zmq_msg_send(&reply, respond, 0);
        zmq_msg_close(&reply);
    }
    zmq_close(respond);
    zmq_ctx_destroy(context);

}