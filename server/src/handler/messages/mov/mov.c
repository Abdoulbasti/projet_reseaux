#include "handler/mov/mov.h"

int parse_mov(char *data, mov_t *mov_m)
{
    int offset = SPACE_LEN;
    memcpy(mov_m->d, data + offset, D_LEN);
    offset += D_LEN;
    return offset;
}

int mov(int client_socket, tcpmessage_t *message, int direction)
{
    mov_t *mov_m = (mov_t *)malloc(sizeof(mov_t));
    if (parse_mov(message->data, mov_m) != message->data_len)
    {
        return 0;
    }
    game_t *game = NULL;
    entity_t *entity = NULL;
    player_t *player = NULL;
    char x[XY_LEN];
    char y[XY_LEN];
    char p[P_LEN];

    int m;
    switch ((m = move_entity(client_socket, direction, str_to_u16(mov_m->d, D_LEN), &game, &entity)))
    {
    case NOTHING:
    case WALL:
    case PLAYER:
        send_moveres(client_socket, u16_to_str(entity->x, x, XY_LEN), u16_to_str(entity->y, y, XY_LEN));
        break;
    case FANTOM:
        player = (player_t *)entity->entity_informations;
        player->point = player->point + 1;
        send_movef(client_socket, u16_to_str(entity->x, x, XY_LEN), u16_to_str(entity->y, y, XY_LEN), u16_to_str(player->point, p, P_LEN));
        if(end_game(game, client_socket) == 0){
            m = -1;
        }
        break;
    }
    free(mov_m);
    return m;
}