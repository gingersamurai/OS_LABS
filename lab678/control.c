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
    int rc = execl("./build/comput", "./build/comput", "6", NULL);
    perror(NULL);
}