#ifndef SERVER_UDP_SEND_H
#define SERVER_UDP_SEND_H 

#include <endian.h>
#include <arpa/inet.h>

#include "protocol/protocol.h"

#define UDP_END "+++"
#define UDP_END_LEN 3

// envoyer un message
ssize_t send_multi(game_t *game, char type[TYPE_LEN], char *message, int len, char *end, int endlen);

#endif // SERVER_UDP_SEND_H
