#include "handler/tcp_message_handler.h"

int unreg(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d",
           *client_socket,
           message->type,
           inet_ntoa(address->sin_addr),
           htons(address->sin_port));

    int game_id = remove_entity(*client_socket);

    if (game_id < 0)
    {
        return 0;
    }

    remove_handler(*client_socket, START);
    remove_handler(*client_socket, UNREG);
    add_handler(*client_socket, NEWPL, newpl);
    add_handler(*client_socket, REGIS, regis);
    send_unrok(*client_socket, (uint8_t)game_id);

    game_t *game = get_game(game_id);

    if (start_game(game) == 0)
    {
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
    }
    return 1;
}