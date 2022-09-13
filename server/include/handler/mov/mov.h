#ifndef MOV_H
#define MOV_H

#include "handler/tcp_message_handler.h"

// bouger un client
int mov(int client_socket, tcpmessage_t *message, int direction);

#endif // MOV_H