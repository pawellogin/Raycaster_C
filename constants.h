#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "raylib.h"

#define SCREEN_SMALL_HEIGHT 480
#define SCREEN_SMALL_WIDTH 640

typedef enum TILE_TYPE {
    EMPTY = 0,
    SOLID = 1
}TILE_TYPE;

typedef enum SIDE {
    VERTICAL = 0,
    HORIZONTAL = 1
} SIDE;

#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define MAP_GRID_SIZE 64

#define MINIMAP_SCALE 10 

#define PLAYER_MOVEMENT_SPEED 3
#define PLAYER_ROTATION_SPEED (3 * DEG2RAD)

#define NEARBLACK CLITERAL(Color){15,15,15,255}

#endif