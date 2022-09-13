#include "handler/tcp_message_handler.h"

int start(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d",
           *client_socket,
           message->type,
           inet_ntoa(address->sin_addr),
           htons(address->sin_port));
    entity_t *player = NULL;
    game_t *game = get_entity_game(*client_socket, &player);

    if (game == NULL || player == NULL)
    {
        return 0;
    }

    player->entity_state = player->entity_state | READY;

    if (start_game(game) < 0)
    {
        remove_handler(*client_socket, START);
        remove_handler(*client_socket, UNREG);
        remove_handler(*client_socket, SIZER);
        remove_handler(*client_socket, LISTR);
        remove_handler(*client_socket, GAMER);
        return 1;
    }

    void *send_welco_posit_element(void *acc, bst_node_t *node)
    {
        entity_t *entity = (entity_t *)node->value;
        if (entity->entity_type == PLAYER)
        {
            player_t *player = (player_t *)entity->entity_informations;
            char x[XY_LEN];
            char y[XY_LEN];
            char udp_port[PORT_LEN];

            remove_handler(entity->entity_id, START);
            remove_handler(entity->entity_id, UNREG);
            remove_handler(entity->entity_id, SIZER);
            remove_handler(entity->entity_id, LISTR);
            remove_handler(entity->entity_id, GAMER);

            add_handler(entity->entity_id, UPMOV, upmov);
            add_handler(entity->entity_id, LEMOV, lemov);
            add_handler(entity->entity_id, DOMOV, domov);
            add_handler(entity->entity_id, RIMOV, rimov);
            add_handler(entity->entity_id, IQUIT, iquit);

            add_handler(entity->entity_id, GLISR, glisreq);
            add_handler(entity->entity_id, MALLR, mallreq);
            add_handler(entity->entity_id, SENDR, sendreq);

            send_welco(entity->entity_id, game->m, game->laby->h, game->laby->w,
                       entities_count(game, FANTOM),
                       ip_to_str(game->multicast_ip),
                       u16_to_str(htons(get_server_multi_port()), udp_port, PORT_LEN));
            send_posit(entity->entity_id, player->id, u16_to_str(entity->x, x, XY_LEN), u16_to_str(entity->y, y, XY_LEN));
        }
        return acc;
    }
    bin_loop(game->entities, NULL, send_welco_posit_element);
    
    int s = send_multi(game, "ENTER", " new player", 10, UDP_END, UDP_END_LEN);
    if(s < 0) perror("send multi");
    
    return 1;
}