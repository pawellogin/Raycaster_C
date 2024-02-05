#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "constants.h"
#include "structures.h"

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
            {2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 2},
            {2, 0, 0, 0, 3, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 2},
            {2, 0, 0, 0, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2},
            {2, 0, 0, 0, 3, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 2},
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


TILE_TYPE mapGiveTileType(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position) {
    Vector2 gridPos = {
        position.x,
        position.y 
    };

    int x = (int)gridPos.x;
    int y = (int)gridPos.y;

    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return map[x][y];  
    } else {
        return ERROR;
    }
}



#endif 
