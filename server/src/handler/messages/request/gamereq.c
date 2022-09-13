#include "handler/tcp_message_handler.h"

int gamereq(int *client_socket, struct sockaddr_in *address, tcpmessage_t *message)
{
    logger("client-message", "(%d) %s %s:%d",
           *client_socket,
           message->type,
           inet_ntoa(address->sin_addr),
           htons(address->sin_port));

    if (send_games(*client_socket, games_count(0)) < 0)
    {
        return -1;
    }
    void *send_ogame_element(void *acc, bst_node_t *node)
    {
        game_t *game = (game_t *)node->value;
        if ((game->state & READY) != READY)
        {
            send_ogame(*client_socket, (uint8_t)node->id, entities_count(game, PLAYER));
        }
        return acc;
    }
    games_loop(NULL, send_ogame_element);
    return 1;
}