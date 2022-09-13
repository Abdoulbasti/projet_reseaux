#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "protocol/protocol.h"

#include "../src/game/labyrinth.c"

#define MAX_UINT8 0xff
#define READY 0b00000001

// structure du jeu
typedef struct game {
    uint8_t m;
    laby_t * laby;
    bst_node_t * entities;
    uint8_t state;

    int multicast_socket;
    struct sockaddr * multicast_ip;
} game_t;

// structure des entitées
typedef struct entity {
    int entity_id;
    int entity_type;
    uint8_t entity_state;
    uint16_t x;
    uint16_t y;
    void * entity_informations;
} entity_t;

// structure des joueurs
typedef struct player_entity {
    char id[ID_LEN];
    char port[PORT_LEN];
    uint16_t point;
} player_t;

// structure des fantomes ( inutiles pour l'instant )
typedef struct fantom_entity {
    int life;
} fantom_t;

// créer une entité
entity_t *new_entity(int id, int type, uint16_t x, uint16_t y, uint8_t state, void *informations);
// créer un joueur
entity_t *new_player(int socket, char id[ID_LEN], char port[PORT_LEN]);
// créer un fantome
entity_t *new_fantom(int id);

// créer un jeu
game_t *new_game(uint8_t m, uint16_t h, uint16_t w);

// ajouter une entité
int add_entity(uint8_t m, entity_t *e);
// retirer une entité
int remove_entity(int e);
// déplacer une entité
int move_entity(int e, int direction, uint16_t d, game_t **game, entity_t **entity);
// bouger dans le labyrinth
int move_laby(laby_t *l, uint16_t *x, uint16_t *y, int direction, uint16_t count, bst_node_t * entities);

// ajouter un jeu
int add_game(uint8_t m, uint16_t h, uint16_t w);
// retirer un jeu
int remove_game(uint8_t m);

// commencer le jeu
int start_game(game_t *game);
// terminer le jeu
int end_game(game_t *game, int initier);

// obtenir le jeu d'une entité 
game_t *get_entity_game(int e, entity_t **entity);
// obtenir un jeu
game_t *get_game(unsigned int id);

// obtenir le nombre de jeu 
uint8_t games_count(int state);
// obtenir le nombre d'entité d'un jeu
uint8_t entities_count(game_t *game, int entities);

// obtenir un id
int new_game_id();
// bin_loop sur l'ensemble des jeu
void *games_loop(void *acc, void *(* loop_fn)(void *acc, bst_node_t *node));
#endif // GAME_H
