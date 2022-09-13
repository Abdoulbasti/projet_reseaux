#include "server/server_udp_send.h"

ssize_t send_multi(game_t *game, char type[TYPE_LEN], char *message, int len, char *end, int endlen)
{    
    struct sockaddr_in addr = *((struct sockaddr_in *)game->multicast_ip);
    socklen_t addrlen = (socklen_t)sizeof(addr);

    char new_message[TYPE_LEN + len + endlen];
    int offset = 0;
    memcpy(new_message, type, TYPE_LEN);
    offset += TYPE_LEN;
    if (len > 0 && message != NULL)
    {
        memcpy(new_message + offset, message, len);
        offset += len;
    }
    memcpy(new_message + offset, end, endlen);
    offset += endlen;
    int r = sendto(game->multicast_socket, new_message, offset, 0, (struct sockaddr *)&addr, addrlen);
    logger("test", "send game multi socket (%d) - return (%d)", game->m, r);
    return r;
}