#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>
#include <log.h>

#include "map.h"
#include "tree.h"

int main(int argc, const char **argv) {
    log_info("node %d started work", atoi(argv[1]));
}