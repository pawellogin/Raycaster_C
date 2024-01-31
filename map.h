#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "constants.h"

typedef struct Map_t {
    TILE_TYPE grid[MAP_HEIGHT][MAP_WIDTH];
} Map;

Map mapCreate();
TILE_TYPE mapGiveTileType(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position);



Map mapCreate() {

    return(Map) {
        .grid = 
        {
            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2},
            {2, 0, 3, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2},
            {2, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 2},
            {2, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2},
            {2, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}
        }
    };
}


TILE_TYPE mapGiveTileType(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position){
    Vector2 gridPos = {(int)(position.x / MAP_GRID_SIZE),(int)(position.y / MAP_GRID_SIZE)};

    int x = gridPos.x;
    int y = gridPos.y;

    return(map[x][y]);
}


#endif 
