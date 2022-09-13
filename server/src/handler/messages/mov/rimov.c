#include "handler/tcp_message_handler.h"

int rimov(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d",
           *client_socket,
           message->type,
           inet_ntoa(address->sin_addr),
           htons(address->sin_port));

    return mov(*client_socket, message, EAST);
}