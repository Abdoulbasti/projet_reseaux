#ifndef SERVER_H
#define SERVER_H 

#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include "../src/server/server_args.c"
#include "../src/logger/logger.c"
#include "../src/binary_tree/binary_tree.c"
#include "../src/server/server_udp_create.c"
#include "../src/game/game.c"
#include "../src/server/server_udp_send.c"

#include "../src/server/server_tcp_send.c"
#include "../src/server/server_tcp_create.c"
#include "../src/server/server_tcp_accept.c"
#include "../src/server/server_tcp_receive.c"

#endif // SERVER_H