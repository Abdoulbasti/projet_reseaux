#ifndef LABYRINTH_H
#define LABYRINTH_H

#define NORTH 0
#define NORTHEAST 1
#define EAST 2
#define SOUTHEAST 3
#define SOUTH 4
#define SOUTHWEST 5
#define WEST 6
#define NORTHEST 7

#define NOTHING 0b00000001
#define WALL 0b00000010
#define PLAYER 0b00000100
#define FANTOM 0b00001000

// structure d'une case
typedef struct cell {
    int value;
    uint8_t state;
} cell_t;
// structure d'un labyrinth
typedef struct labyrinth
{
    uint16_t h;
    uint16_t w;
    cell_t *cells;
} laby_t;

// créer un labyrinth
laby_t *new_laby(uint16_t h, uint16_t w);
// modifier une case
cell_t *set_cell(laby_t *l, uint16_t x, uint16_t y, int value, uint8_t state);
// obtenir une case
cell_t *get_cell(laby_t *l, uint16_t x, uint16_t y);
// obtenir les case adjacentes d'une case
int *near_cell(laby_t *l, uint16_t x, uint16_t y);
// modifier d'un labyrinth à partir d'un texte
laby_t * set_array(laby_t *l, char * l_str, int len);

#endif // LABYRINTH_H