#ifndef DEBUG_H
#define DEBUG_H

#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "raycaster.h"


void debugDrawMiniMap(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position, Vector2 direction);
void debugDrawPlayerInfo(Vector2 position, Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);


void debugDrawMiniMap(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position, Vector2 direction){

    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j< MAP_WIDTH;j++){
            if(map[i][j] == EMPTY )
            {
                DrawRectangle(i*MINIMAP_SCALE + MINIMAP_OFFSET_X,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,LIGHTGRAY);
            }
            else if(map[i][j] == SOLID)
            {
                DrawRectangle(i*MINIMAP_SCALE + MINIMAP_OFFSET_X,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,DARKGRAY);
            }           
        }
    }

    position.x = (position.x / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    position.x += MINIMAP_OFFSET_X;
    
    position.y = (position.y / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    

    DrawCircleV(position,0.3*MINIMAP_SCALE,RED);

    Vector2 lineEnd = {position.x + MINIMAP_SCALE * direction.x, position.y + MINIMAP_SCALE * direction.y,};

    //DrawLineV(position,lineEnd,GREEN);
}

void debugDrawPlayerInfo(Vector2 position,Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    char positionText[40];
    snprintf(positionText,sizeof(positionText),"Position: X = %.2f Y = %.2f",position.x, position.y);
    DrawText(positionText,10,10,20,GREEN);

    char angleText[40];
    snprintf(angleText,sizeof(angleText),"Angle: %.2f",angle);
    DrawText(angleText,10,30,20,GREEN);

    char currentTileText[40];
    snprintf(currentTileText,sizeof(currentTileText),"Current tile: %d",mapGiveTileType(map,position));
    DrawText(currentTileText,10,50,20,GREEN);

    char singleRayLenght[40];
    float lenght = 0;
    TILE_TYPE _t;
    SIDE _s;
    raycasterCastRay(&lenght,&_t,&_s,position,direction,map);
    snprintf(singleRayLenght,sizeof(singleRayLenght),"Current tile: %.2f",lenght);
    DrawText(singleRayLenght,10,70,20,GREEN);
}

void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){

    float length = 0;
    TILE_TYPE tile = EMPTY;
    SIDE side = HORIZONTAL;

    raycasterCastRay(&length, &tile, &side, position, direction, map);

    Vector2 endPosition = {
        position.x + direction.x * length,
        position.y + direction.y * length
    };

    position.x = (position.x / MAP_GRID_SIZE ) * MINIMAP_SCALE ;
    position.x += MINIMAP_OFFSET_X;
    position.y = (position.y / MAP_GRID_SIZE ) * MINIMAP_SCALE;

    endPosition.x = (endPosition.x / MAP_GRID_SIZE ) * MINIMAP_SCALE  ;
    endPosition.x += MINIMAP_OFFSET_X;
    endPosition.y = (endPosition.y / MAP_GRID_SIZE ) * MINIMAP_SCALE  ;

    DrawLineV(position,endPosition,GREEN);
}

#endif
