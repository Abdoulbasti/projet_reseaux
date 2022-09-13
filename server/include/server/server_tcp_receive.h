#ifndef SERVER_TCP_RECEIVE_H
#define SERVER_TCP_RECEIVE_H 

#include <stdlib.h>
#include <pthread.h>

#define BUFFER_MAX_LEN 2048
#define BUFFER_LEN 128

#include "server/server_tcp_message.h"

#include "../src/handler/tcp_message_handler.c"

// gérer les données reçu par un client ( thread )
void * server_tcp_receive(void * arg);

#endif // SERVER_TCP_RECEIVE_H
