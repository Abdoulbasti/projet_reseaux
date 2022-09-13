#ifndef SERVER_TCP_ACCEPT_H
#define SERVER_TCP_ACCEPT_H 

#include <arpa/inet.h>
#include <pthread.h>

#include "protocol/protocol.h"

// structure de l'argument du thread d'acceptation d'un client
typedef struct server_accept_args {
    int socket;
    struct sockaddr_in address;
    int (* message_handler)(int * client_socket, struct sockaddr_in * address, tcpmessage_t * message);
} server_accept_t;

// accepter des clients sur une socket
int server_tcp_accept(int socket_d,
                      void *(*client_accepted_handler)(void *arg),
                      int (*message_handler)(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message));

#endif // SERVER_TCP_ACCEPT_H
