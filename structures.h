#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants.h"
 
typedef struct TileToDraw_t TileToDraw;

typedef struct TileToDraw_t
{
    float rayLength;
    TILE_TYPE tile;
    SIDE side;   
}TileToDraw;

 #endif