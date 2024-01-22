#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "map.h"


void debugDrawMiniMap(Map map, Player player);
void debugDrawPlayerInfo(Player player,Map map);


void debugDrawMiniMap(Map map, Player player){
    int offsetX = SCREEN_SMALL_HEIGHT ;
    //int offsetY;


    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j< MAP_WIDTH;j++){
            if(map.grid[i][j] == EMPTY )
            {
                DrawRectangle(i*MINIMAP_SCALE + offsetX,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,LIGHTGRAY);
            }
            else if(map.grid[i][j] == SOLID)
            {
                DrawRectangle(i*MINIMAP_SCALE + offsetX,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,DARKGRAY);
            }           
        }
    }

    player.position.x = (player.position.x / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    player.position.x += offsetX;
    
    player.position.y = (player.position.y / MAP_GRID_SIZE ) * MINIMAP_SCALE;
    

    DrawCircleV(player.position,0.3*MINIMAP_SCALE,RED);

    Vector2 lineEnd = {player.position.x + MINIMAP_SCALE * player.direction.x, player.position.y + MINIMAP_SCALE * player.direction.y,};

    DrawLineV(player.position,lineEnd,GREEN);
}

void debugDrawPlayerInfo(Player player,Map map){
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
