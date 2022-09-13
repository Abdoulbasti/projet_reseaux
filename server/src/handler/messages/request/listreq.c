#include "handler/tcp_message_handler.h"

int parse_listreq(char * data, listreq_t *listreq_m){
    int offset = SPACE_LEN;
    memcpy(&listreq_m->m, data + offset, sizeof(listreq_m->m));
    offset += sizeof(listreq_m->m);
    return offset;
}

int listreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d", 
                                            *client_socket, 
                                            message->type,
                                            inet_ntoa(address->sin_addr), 
                                            htons(address->sin_port));
    listreq_t * listreq_m = (listreq_t *)malloc(sizeof(listreq_t));
    if(parse_listreq(message->data, listreq_m) != message->data_len){
        return 0;
    }
    game_t *game;
    if((game = get_game(listreq_m->m)) == NULL){
        return 0;
    }         
    send_listres(*client_socket, game->m, entities_count(game, PLAYER));
    void *send_playr_element(void *acc, bst_node_t *node){
        entity_t *entity = (entity_t *)node->value;
        if(entity != NULL && entity->entity_type == PLAYER){
            player_t *player = (player_t *)entity->entity_informations;
            send_playr(*client_socket, player->id);
        }
        return acc;
    }
    bin_loop(game->entities, NULL, send_playr_element);
    free(listreq_m);
    return 1;
}