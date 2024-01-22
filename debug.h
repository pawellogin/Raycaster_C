#ifndef DEBUG_H
#define DEBUG_H

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "map.h"


void debugDrawMiniMap(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position, Vector2 direction);
void debugDrawPlayerInfo(Player player,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
//void debugDrawPlayerRaySingle(Vector2 position);


void debugDrawMiniMap(TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH], Vector2 position, Vector2 direction){
    int offsetX = SCREEN_SMALL_WIDTH - MINIMAP_SCALE * MAP_WIDTH;
    //int offsetY;


    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j< MAP_WIDTH;j++){
            if(map[i][j] == EMPTY )
            {
                DrawRectangle(i*MINIMAP_SCALE + offsetX,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,LIGHTGRAY);
            }
            else if(map[i][j] == SOLID)
            {
                DrawRectangle(i*MINIMAP_SCALE + offsetX,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,DARKGRAY);
            }           
        }
    }

    position.x = (position.x / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    position.x += offsetX;
    
    position.y = (position.y / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    

    DrawCircleV(position,0.3*MINIMAP_SCALE,RED);

    Vector2 lineEnd = {position.x + MINIMAP_SCALE * direction.x, position.y + MINIMAP_SCALE * direction.y,};

    DrawLineV(position,lineEnd,GREEN);
}

void debugDrawPlayerInfo(Player player,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    char positionText[40];
    snprintf(positionText,sizeof(positionText),"Position: X = %.2f Y = %.2f",player.position.x, player.position.y);
    DrawText(positionText,10,10,20,GREEN);

    char angleText[40];
    snprintf(angleText,sizeof(angleText),"Angle: %.2f",player.angle);
    DrawText(angleText,10,30,20,GREEN);

    char currentTileText[40];
    snprintf(currentTileText,sizeof(currentTileText),"Current tile: %d",mapGiveTileType(map,player.position));
    DrawText(currentTileText,10,50,20,GREEN);

}

#endif
