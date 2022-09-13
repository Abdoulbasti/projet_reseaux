#include "handler/tcp_message_handler.h"

int parse_sizereq(char * data, sizereq_t *sizereq_m){
    int offset = SPACE_LEN;
    memcpy(&sizereq_m->m, data + offset, sizeof(sizereq_m->m));
    offset += sizeof(sizereq_m->m);
    return offset;
}

int sizereq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d", 
                                            *client_socket, 
                                            message->type,
                                            inet_ntoa(address->sin_addr), 
                                            htons(address->sin_port));
    sizereq_t * sizereq_m = (sizereq_t *)malloc(sizeof(sizereq_t));
    if(parse_sizereq(message->data, sizereq_m) != message->data_len){
        return 0;
    }
    game_t *game;
    if((game = get_game(sizereq_m->m)) == NULL){
        return 0;
    } 
    send_sizeres(*client_socket, game->m, game->laby->h, game->laby->w);
    return 1;
}