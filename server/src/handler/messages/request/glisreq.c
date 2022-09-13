#include "handler/tcp_message_handler.h"

int glisreq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d", 
                                            *client_socket, 
                                            message->type,
                                            inet_ntoa(address->sin_addr), 
                                            htons(address->sin_port));

    game_t *game = get_entity_game(*client_socket, NULL);

    send_glisres(*client_socket, entities_count(game, FANTOM));
    void *send_gplyr_element(void *acc, bst_node_t *node){
        entity_t *entity = (entity_t *)node->value;
        if(entity != NULL && entity->entity_type == PLAYER){
            player_t *player = (player_t *)entity->entity_informations;
            char x[XY_LEN];
            char y[XY_LEN];
            char p[P_LEN];
            send_gplyr(*client_socket, player->id, u16_to_str(entity->x, x, XY_LEN), u16_to_str(entity->y, y, XY_LEN), u16_to_str(player->point, p, P_LEN));
        }
        return acc;
    }
    bin_loop(game->entities, NULL, send_gplyr_element);
    return 1;
}