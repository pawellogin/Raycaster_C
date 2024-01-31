#ifndef DEBUG_H
#define DEBUG_H

#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "raycaster.h"


void debugDrawMiniMap(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position, Vector2 direction);
void debugDrawPlayerInfo(Vector2 position, Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
Vector2 debugConvertToMinimapSize(Vector2 positionToConvert);

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

    DrawLineEx(position,lineEnd,2,TEXT_COLOR);
}

void debugDrawPlayerInfo(Vector2 position,Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    char positionText[40];
    snprintf(positionText,sizeof(positionText),"Position: X = %.2f Y = %.2f",position.x, position.y);
    DrawText(positionText,10,10,20,TEXT_COLOR);

    char angleText[40];
    snprintf(angleText,sizeof(angleText),"Angle: %.2f",angle * RAD2DEG);
    DrawText(angleText,10,30,20,TEXT_COLOR);

    char currentTileText[40];
    const float DETECTION_LENGTH = MAP_GRID_SIZE;
    Vector2 poitingAtPosition = {position.x + DETECTION_LENGTH * direction.x, position.y + DETECTION_LENGTH * direction.y,};
    snprintf(currentTileText,sizeof(currentTileText),"Poiting at tile: %d",mapGiveTileType(map,poitingAtPosition));
    DrawText(currentTileText,10,50,20,TEXT_COLOR);

    char singleRaylength[40];
    float length = 0;
    TILE_TYPE _t;
    SIDE _s;
    //raycasterCastRay(&length,&_t,&_s,position,direction,map);
    snprintf(singleRaylength,sizeof(singleRaylength),"Single ray length: %.2f",length);
    DrawText(singleRaylength,10,70,20,TEXT_COLOR);
}

void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){

    float length = 0;
    TILE_TYPE tile = EMPTY;
    SIDE side = HORIZONTAL;

    //raycasterCastRay(&length, &tile, &side, position, direction, map);

    Vector2 endPosition = {
        position.x + direction.x * length,
        position.y + direction.y * length
    };

    position = debugConvertToMinimapSize(position);

    endPosition = debugConvertToMinimapSize(endPosition);

    DrawLineV(position,endPosition,GREEN);
}

Vector2 debugConvertToMinimapSize(Vector2 positionToConvert){
    positionToConvert.x = (positionToConvert.x / MAP_GRID_SIZE ) * MINIMAP_SCALE ;
    positionToConvert.x += MINIMAP_OFFSET_X;

    positionToConvert.y = (positionToConvert.y / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    positionToConvert.y += MINIMAP_OFFSET_Y;

    return positionToConvert;
}

#endif
