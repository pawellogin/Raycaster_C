#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants.h"
 
typedef enum TILE_TYPE TILE_TYPE;
typedef struct TileToDraw_t TileToDraw;
const char * tileTypeToString(TILE_TYPE type);
typedef enum SIDE SIDE;

typedef enum TILE_TYPE {
    ERROR = -1,
    EMPTY = 0,
    SOLID = 1,
    BARRIER = 2,
    GLASS = 3
} TILE_TYPE;

typedef enum SIDE {
    VERTICAL = 0,
    HORIZONTAL = 1
} SIDE;

typedef struct TileToDraw_t
{
    float rayLength;
    TILE_TYPE tile;
    SIDE side;
    Vector2 cords; 
}TileToDraw;

const char* tileTypeToString(TILE_TYPE type) {
    switch(type) {
        case ERROR: return "ERROR";
        case EMPTY: return "EMPTY";
        case SOLID: return "SOLID";
        case BARRIER: return "BARRIER";
        case GLASS: return "GLASS";
        default: return "UNKNOWN";
    }
}

 #endif