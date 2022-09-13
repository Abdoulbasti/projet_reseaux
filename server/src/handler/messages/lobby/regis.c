#include "handler/tcp_message_handler.h"

int parse_regis(char * data, regis_t *regis_m){
    int offset = SPACE_LEN;
    memcpy(regis_m->id, data + offset, ID_LEN);
    offset += ID_LEN + SPACE_LEN;
    memcpy(regis_m->port, data + offset, PORT_LEN);
    offset += PORT_LEN + SPACE_LEN;
    memcpy(&regis_m->m, data + offset, sizeof(regis_m->m));
    offset += sizeof(regis_m->m);
    logger("test", "offset: %d", offset);
    return offset;
}

int regis(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d", 
                                            *client_socket, 
                                            message->type,
                                            inet_ntoa(address->sin_addr), 
                                            htons(address->sin_port));
    
    regis_t * regis_m = (regis_t *)malloc(sizeof(regis_t));
    if(parse_regis(message->data, regis_m) != message->data_len){
        return 0;
    }

    if(add_entity(regis_m->m, new_player(*client_socket, regis_m->id, regis_m->port)) < 0){
        send_regno(*client_socket);
        return 1;
    }

    remove_handler(*client_socket, NEWPL);
    remove_handler(*client_socket, REGIS);
    add_handler(*client_socket, START, start);
    add_handler(*client_socket, UNREG, unreg);
    send_regok(*client_socket, regis_m->m);
    free(regis_m);
    return 1;
}