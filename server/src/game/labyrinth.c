#include "game/labyrinth.h"

/**
 *
 * fonction new_laby h:number w:number
 *
 * créer un nouveau labyrinth
 * retourne un pointeur vers le nouveau labyrinth
 * 
 */
laby_t *new_laby(uint16_t h, uint16_t w)
{
    laby_t *p = malloc(sizeof(laby_t));
    p->h = h;
    p->w = w;
    p->cells = malloc((h * w) * sizeof(cell_t));
    memset(p->cells, 0, (h * w) * sizeof(cell_t));
    return p;
}

/**
 *
 * fonction set_cell l:* x:number y:number value:number state:number
 *
 * modifier une case du labyrinth
 * retourne la case modifié ( NULL si aucune case )
 * 
 */
cell_t *set_cell(laby_t *l, uint16_t x, uint16_t y, int value, uint8_t state)
{
    if (x < l->w && y < l->h)
    {
        (l->cells + ((y * l->w) + x))->value = value;
        (l->cells + ((y * l->w) + x))->state = state;
        return l->cells + ((y * l->w) + x);
    }
    else
    {
        return NULL;
    }
}

/**
 *
 * fonction get_cell l:* x:number y:number
 *
 * obtenir une case du labyrinth
 * retourne la case demandé ( NULL si aucune case )
 * 
 */
cell_t *get_cell(laby_t *l, uint16_t x, uint16_t y)
{
    if (x < l->w && y < l->h)
    {
        return l->cells + ((y * l->w) + x);
    }
    else
    {
        return NULL;
    }
}

/**
 *
 * fonction near_cell l:* x:number y:number
 *
 * obtenir les cases adjacentes d'une case du labyrinth
 * retourne les cases adjacentes
 * 
 */
int *near_cell(laby_t *l, uint16_t x, uint16_t y)
{
    int *near = (int *)malloc(8);
    memset(near, 0, 8);
    if (y > 0)
    {
        near[NORTH] = ((y - 1) * l->w) + x;
    }
    else
    {
        near[NORTH] = -1;
    }
    if (x < (l->w - 1))
    {
        near[EAST] = (y * l->w) + x + 1;
    }
    else
    {
        near[EAST] = -1;
    }
    if (y < (l->h - 1) && x < (l->w - 1))
    {
        near[SOUTHEAST] = ((y + 1) * l->w) + x + 1;
    }
    else
    {
        near[SOUTHEAST] = -1;
    }
    if (y < (l->h - 1))
    {
        near[SOUTH] = ((y + 1) * l->w) + x;
    }
    else
    {
        near[SOUTH] = -1;
    }
    if (y < (l->h - 1) && x > 0)
    {
        near[SOUTHWEST] = ((y + 1) * l->w) + x - 1;
    }
    else
    {
        near[SOUTHWEST] = -1;
    }
    if (x > 0)
    {
        near[WEST] = (y * l->w) + x - 1;
    }
    else
    {
        near[WEST] = -1;
    }
    if (y > 0 && x > 0)
    {
        near[NORTHEST] = ((y - 1) * l->w) + x - 1;
    }
    else
    {
        near[NORTHEST] = -1;
    }
    return near;
}

/**
 *
 * fonction set_array l:* l_str:string len:number
 *
 * définir un tableau à partir d'une chaine de character
 * retourne le labyrinth modifié
 * 
 */
laby_t *set_array(laby_t *l, char *l_str, int len)
{
    if (l->w * l->h != len)
    {
        return l;
    }
    for (uint16_t y = 0; y < l->h; y++)
    {
        for (uint16_t x = 0; x < l->w; x++)
        {
            int id = (y * l->w) + x;
            switch (l_str[id])
            {
            case '1':
                set_cell(l, x, y, id, NOTHING);
                break;
            case '0':
                set_cell(l, x, y, id, WALL);
                break;
            default:
                set_cell(l, x, y, id, WALL);
                break;
            }
        }
    }
    return l;
}