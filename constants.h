#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "raylib.h"

#define SCREEN_HEIGHT 900
#define SCREEN_WIDTH 1600

typedef enum TILE_TYPE {
    EMPTY = 0,
    SOLID = 1,
    BARRIER = 2,
    GLASS = 3
}TILE_TYPE;

typedef enum SIDE {
    VERTICAL = 0,
    HORIZONTAL = 1
} SIDE;

typedef struct WallToPrint_t {
    TILE_TYPE tile;
    float lenght;
    SIDE side;
} WallToPrint;

#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define MAP_GRID_SIZE 64

#define MINIMAP_SCALE 10
#define MINIMAP_OFFSET_X (SCREEN_WIDTH - MINIMAP_SCALE * MAP_WIDTH)
#define MINIMAP_OFFSET_Y 0 

#define PLAYER_MOVEMENT_SPEED 3
#define PLAYER_ROTATION_SPEED (3 * DEG2RAD)
#define PLAYER_POV (60.0f * DEG2RAD)

#define NEARBLACK CLITERAL(Color){15,15,15,255}
#define SHADOW_POWER (1.0f/1000.0f)

#define TEXT_COLOR BLACK

#endif