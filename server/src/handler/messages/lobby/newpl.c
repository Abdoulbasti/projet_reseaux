#include "handler/tcp_message_handler.h"

int parse_newpl(char * data, newpl_t *newpl_m){
    int offset = SPACE_LEN;
    memcpy(newpl_m->id, data + offset, ID_LEN);
    offset += ID_LEN + SPACE_LEN;
    memcpy(newpl_m->port, data + offset, PORT_LEN);
    offset += PORT_LEN;
    return offset;
}

int newpl(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d", 
                                            *client_socket, 
                                            message->type,
                                            inet_ntoa(address->sin_addr), 
                                            htons(address->sin_port));

    newpl_t * newpl_m = (newpl_t *)malloc(sizeof(newpl_t));
    if(parse_newpl(message->data, newpl_m) != message->data_len){
        return 0;
    }

    uint8_t m = (uint8_t)new_game_id();
    if(add_game(m, 6, 7) < 0){
        send_regno(*client_socket);
        return 1;
    }

    if(add_entity(m, new_player(*client_socket, newpl_m->id, newpl_m->port)) < 0){
        send_regno(*client_socket);
        return 1;
    }

    remove_handler(*client_socket, NEWPL);
    remove_handler(*client_socket, REGIS);
    add_handler(*client_socket, START, start);
    add_handler(*client_socket, UNREG, unreg);
    send_regok(*client_socket, m);
    free(newpl_m);
    return 1;
}