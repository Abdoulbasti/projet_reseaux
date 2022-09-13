#include "game/game.h"

bst_node_t *games = NULL;

/**
 *
 * fonction new_game m:number h:number w:number
 *
 * créer un jeu
 * retourne un pointeur vers le nouveau jeu
 * 
 */
game_t *new_game(uint8_t m, uint16_t h, uint16_t w)
{
    char ip[16];
    memset(ip, 0, 16);
    sprintf(ip, "224.0.0.%d", m);

    char port[6];
    memset(port, 0, 6);
    sprintf(port, "%d", get_server_multi_port());

    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->m = m;
    game->laby = new_laby(h, w);
    game->entities = NULL;
    game->state = 0;
    game->multicast_socket = multicast_udp_create(ip, port, &game->multicast_ip);
    return game;
}

/**
 *
 * fonction add_game m:number h:number w:number
 *
 * ajouter un jeu à la liste des jeu
 * retourne l'id du jeu
 * 
 */
int add_game(uint8_t m, uint16_t h, uint16_t w)
{
    if (games == NULL)
    {
        games = new_bst(m, new_game(m, h, w));
        return 0;
    }

    if (search(games, m) == NULL)
    {
        insert_bst(games, m, new_game(m, h, w));
        return 0;
    }

    return -1;
}

/**
 *
 * fonction remove_game m:number
 *
 * retirer un jeu de la liste des jeu
 * retourne l'id du jeu
 * 
 */
int remove_game(uint8_t m)
{
    if (games == NULL)
    {
        return -1;
    }

    if (search(games, m) != NULL)
    {
        games = delete_bst(games, m);
        return 0;
    }

    return -1;
}

/**
 *
 * fonction start_game game:*
 *
 * commencer un jeu
 * retourne 0
 * 
 */
int start_game(game_t *game)
{
    void *check_all_ready(void *acc, bst_node_t *node)
    {
        int *acc_c = (int *)acc;

        entity_t *entity = (entity_t *)node->value;

        if (entity->entity_type == PLAYER)
        {
            *acc_c = *acc_c & entity->entity_state & READY;
        }

        return acc_c;
    }

    int result = READY;

    if (*((int *)bin_loop(game->entities, &result, check_all_ready)) != READY)
    {
        return -1;
    }

    int len = game->laby->h * game->laby->w;
    // to do: char * random_lab_str = get_random_lab(len);
    // to do: set_array(game->laby, random_str, len);
    set_array(game->laby, "010000001011110100100110110001111100000010", len); 

    // add fantom
    int fantom_count = (len / 50) + 1;
    if (fantom_count > 50)
    {
        fantom_count = 50;
    }
    for (int i = 0; i < fantom_count; i++)
    {
        int fantom_id = (game->m << 8) | i;
        // ajouter des fantoms dans le jeu
        add_entity(game->m, new_fantom(fantom_id));
    }
    int free_cells[len];
    int free_cells_count = 0;

    for (int i = 0; i < len; i++)
    {
        int x = i % game->laby->w;
        int y = i / game->laby->w;
        if ((get_cell(game->laby, x, y)->state & NOTHING) == NOTHING)
        {
            free_cells[free_cells_count++] = i;
        }
    }
    // fonction pour définir la position initiale des entités
    void *set_entity_pos(void *acc, bst_node_t *node)
    {
        entity_t *entity = (entity_t *)node->value;
        int free_cell_id = random() % free_cells_count;
        int cell = free_cells[free_cell_id];

        entity->x = cell % game->laby->w;
        entity->y = cell / game->laby->w;

        free_cells[free_cell_id] = free_cells[--free_cells_count];
        return acc;
    }
    bin_loop(game->entities, NULL, set_entity_pos);
    game->state = game->state | READY;

    logger("game", "(%d) start_game entities:%d fantom:%d", game->m, entities_count(game, PLAYER | FANTOM), fantom_count);
    return 0;
}

/**
 *
 * fonction end_game game:* initier:number
 *
 * terminer un jeu
 * retourne 0 ( -1 si erreur )
 * 
 */
int end_game(game_t *game, int initier)
{    
    if(entities_count(game, FANTOM) != 0){
        return -1;
    }

    // fonction pour déconnecter tout les joueurs d'un jeu
    void *disconnect_player(void *acc, bst_node_t *node)
    {
        entity_t *entity = (entity_t *)node->value;

        if (entity->entity_type == PLAYER && entity->entity_id != initier)
        {
            close(entity->entity_id);
        }
        if (entity->entity_informations != NULL)
        {
            free(entity->entity_informations);
        }
        free(entity);
        return acc;
    }

    bin_loop(game->entities, NULL, disconnect_player);
    return remove_game(game->m);
}

/**
 *
 * fonction get_entity_game e:number entity:**
 *
 * obtenir le jeu d'une socket et défini l'entité correspondante
 * retourne le pointeur d'un jeu ( NULL si aucune jeu )
 * 
 */
game_t *get_entity_game(int e, entity_t **entity)
{
    void *get_loop_func(void *acc, bst_node_t *node)
    {
        if(acc != NULL){
            return acc;
        }

        game_t *game = (game_t *)node->value;
        if (game->entities == NULL)
        {
            return acc;
        }

        bst_node_t *entity_node = search(game->entities, e);
        if (entity_node == NULL)
        {
            return acc;
        }
        if (entity != NULL)
        {
            *entity = (entity_t *)entity_node->value;
        }
        return game;
    }

    return (game_t *)games_loop(NULL, get_loop_func);
}

/**
 *
 * fonction get_game e:number entity:**
 *
 * obtenir le jeu d'une socket et défini l'entité correspondante
 * retourne le pointeur d'un jeu ( NULL si aucune jeu )
 * 
 */
game_t *get_game(unsigned int id)
{
    bst_node_t *node = search(games, id);
    if (node == NULL)
    {
        return NULL;
    }
    return (game_t *)node->value;
}

/**
 *
 * fonction new_game_id
 *
 * obtenir un id
 * retourne un entier
 * 
 */
int new_game_id()
{
    bst_node_t *node = maximum(games);
    if (node == NULL)
    {
        return '!';
    }
    return node->id + 1;
}

/**
 *
 * fonction games_count state:number
 *
 * obtenir le nombre de jeu dans un état défini
 * retourne le nombre de jeu
 * 
 */
uint8_t games_count(int state)
{
    void *count(void *acc, bst_node_t *node)
    {
        game_t *game = (game_t *)node->value;
        if (game->entities != NULL && (game->state & state) == game->state)
        {
            uint8_t *acc_c = (uint8_t *)acc;
            *acc_c = *acc_c + 1;
            return acc_c;
        }
        return acc;
    }

    int result = 0;
    return *((uint8_t *)games_loop(&result, count));
}

/**
 *
 * fonction entities_count game:* entities:number
 *
 * obtenir le nombre d'entité d'un jeu dans un état défini
 * retourne le nombre d'entité
 * 
 */
uint8_t entities_count(game_t *game, int entities)
{
    if (game == NULL)
    {
        return 0;
    }

    void *count(void *acc, bst_node_t *node)
    {
        entity_t *entity = (entity_t *)node->value;
        if (entity != NULL && ((entity->entity_type & entities) == entity->entity_type))
        {
            uint8_t *acc_c = (uint8_t *)acc;
            *acc_c = *acc_c + 1;
            return acc_c;
        }
        return acc;
    }

    uint8_t result = 0;
    return *((uint8_t *)bin_loop(game->entities, &result, count));
}

/**
 *
 * fonction games_loop acc:* loop_fn:*
 *
 * bin_loop avec games
 * retourne le pointeur du résultat
 * 
 */
void *games_loop(void *acc, void *(*loop_fn)(void *acc, bst_node_t *node))
{
    return bin_loop(games, acc, loop_fn);
}

/*
 *
 * ENTITY
 *
 *
 */


/**
 *
 * fonction new_entity id:number type:number x:number y:number state:number informations:*
 *
 * créer une nouvelle entité
 * retourne le pointeur de l'entité
 * 
 */
entity_t *new_entity(int id, int type, uint16_t x, uint16_t y, uint8_t state, void *informations)
{
    entity_t *entity = (entity_t *)malloc(sizeof(entity_t));
    entity->entity_id = id;
    entity->entity_type = type;
    entity->x = x;
    entity->y = y;
    entity->entity_state = state;
    entity->entity_informations = informations;
    return entity;
}

/**
 *
 * fonction new_player socket:number id:string port:string
 *
 * créer une nouvelle entité joueur
 * retourne le pointeur de l'entité joueur
 * 
 */
entity_t *new_player(int socket, char id[ID_LEN], char port[PORT_LEN])
{
    player_t *player = (player_t *)malloc(sizeof(player_t));
    memcpy(player->id, id, ID_LEN);
    memcpy(player->port, port, PORT_LEN);
    return new_entity(socket, PLAYER, 0, 0, 0, player);
}

/**
 *
 * fonction new_fantom id:number
 *
 * créer une nouvelle entité fantom
 * retourne le pointeur de l'entité fantom
 * 
 */
entity_t *new_fantom(int id)
{
    return new_entity(id, FANTOM, 0, 0, 0, NULL);
}

/**
 *
 * fonction add_entity m:number e:*
 *
 * ajouter une entité à un jeu
 * retourne 0 ( -1 si erreur )
 * 
 */
int add_entity(uint8_t m, entity_t *e)
{
    game_t *game = get_game(m);

    if (games == NULL || (game->state & READY) == READY)
    {
        return -1;
    }

    if (game->entities == NULL)
    {
        game->entities = new_bst(e->entity_id, e);
    }
    else
    {
        insert_bst(game->entities, e->entity_id, e);
    }
    return 0;
}

/**
 *
 * fonction remove_entity e:number
 *
 * retirer une entité d'un jeu
 * retourne 0 ( -1 si erreur )
 * 
 */
int remove_entity(int e)
{
    game_t *game = get_entity_game(e, NULL);

    if (game == NULL || game->entities == NULL)
    {
        logger("game", "game not found for entity: %d", e);
        return -1;
    }

    // retirer l'entité
    game->entities = delete_bst(game->entities, e);
    // s'il n'y a plus de joueurs
    if (game->entities == NULL || entities_count(game, PLAYER) == 0)
    {   
        // retirer tout les fantoms
        void *remove_all_fantom(void *acc, bst_node_t *node){
            if(node->value != NULL){
                free(node->value);
            }
            free(node);
            return acc;
        }
        bin_loop(game->entities, NULL, remove_all_fantom);
        // supprimer le jeu
        games = delete_bst(games, game->m);
    }
    return game->m;
}

/**
 *
 * fonction move_entity e:number direction:number d:number game:** entity:**
 *
 * déplacer une entité ( défini le jeu et l'entité )
 * retourne 0 ( -1 si erreur )
 * 
 */
int move_entity(int e, int direction, uint16_t d, game_t **game, entity_t **entity)
{
    if (game == NULL || entity == NULL)
    {
        return -1;
    }

    *game = get_entity_game(e, entity);

    if (game == NULL || entity == NULL)
    {
        return -1;
    }

    return move_laby((*game)->laby, &(*entity)->x, &(*entity)->y, direction, d, (*game)->entities);
}

/**
 *
 * fonction move_laby l:* x:* y:* direction:number count:number entities:*
 *
 * déplacer une entité dans un labyrinth
 * retourne le type de l'entité sur la case 
 * 
 */
int move_laby(laby_t *l, uint16_t *x, uint16_t *y, int direction, uint16_t count, bst_node_t *entities)
{
    if (count == 0)
    {
        return NOTHING;
    }

    int *near = near_cell(l, *x, *y);

    int n = near[direction];
    if (n < 0 || ((get_cell(l, n % l->w, n / l->w)->state & WALL) == WALL))
    {
        return WALL;
    }

    uint16_t n_x = n % l->w;
    uint16_t n_y = n / l->w;

    void *get_entity_on_cell(void *acc, bst_node_t *node)
    {
        if (acc == NULL)
        {

            entity_t *entity = (entity_t *)node->value;
            if (entity->x == n_x && entity->y == n_y)
            {
                return entity;
            }
        }
        return acc;
    }

    entity_t *entity_on_cell = (entity_t *)bin_loop(entities, NULL, get_entity_on_cell);
    int type;
    if (entity_on_cell != NULL && (type = entity_on_cell->entity_type) > 0)
    {
        if ((type & FANTOM) == FANTOM)
        {
            logger("game", "fantom (%d) [%d,%d] detected", entity_on_cell->entity_id, n_x, n_y);
            int id = entity_on_cell->entity_id;
            remove_entity(id);

            *x = n_x;
            *y = n_y;
        }
        return type;
    }

    *x = n_x;
    *y = n_y;

    return move_laby(l, x, y, direction, count - 1, entities);
}