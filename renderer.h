#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"
#include "constants.h"
#include "raycaster.h"
#include <math.h>
#include <stdlib.h>

Color rendererConvertTileToColor(TILE_TYPE tile);
Color rendererDarkenColor(Color color, float shadowPower);
Color rendererLimitDarknessTo(Color color, Color limit);
float rendererConvertToWallSize(TILE_TYPE tile);
void rendererDrawWallsSolidColor(Vector2 startPosition, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void rendererDrawCelling(Color color);
void rendererDrawFloor(Color color);



Color rendererConvertTileToColor(TILE_TYPE tile){
    switch (tile)
    {
    case SOLID:
        return LIGHTGRAY;
        break;

    case BARRIER:
        return BLANK;
        break;

    case GLASS:
        return (Color){20,40,230,60};
    
    default:
        return RED;
        break;
    }
}

Color rendererDarkenColor(Color color, float shadowPower) {
    Color darkColorLimit = {40,40,40,255};

    if(shadowPower > 1) color = darkColorLimit;
    else{
        float shadow = color.r * shadowPower;
        color.r -= shadow;

        shadow = color.g * shadowPower;
        color.g -= shadow;

        shadow = color.b * shadowPower;
        color.b -= shadow;

        color = rendererLimitDarknessTo(color, darkColorLimit);

    }

    return color;
}

Color rendererLimitDarknessTo(Color color, Color limit){
    Color result = color;
    if(result.r < limit.r) result.r = limit.r;
    if(result.g < limit.g) result.g = limit.g;
    if(result.b < limit.b) result.b = limit.b;

    return result;
}

float rendererConvertToWallSize(TILE_TYPE tile){
    switch (tile)
    {
    case EMPTY:
        return 0.0f;
        break;

    case SOLID: 
        return 50.0f;
    
    case GLASS:
        return 50.0f;

    default:
        return 0.0f;
        break;
    }
}

void rendererDrawWallsSolidColor(Vector2 startPosition, float startAngle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    float rayAngle = startAngle - playerFOV/2;
    Vector2 rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};
    float rayLength = 0;

    TILE_TYPE tile = EMPTY;
    SIDE side = VERTICAL;

    WallToPrint walls[16];
    int wallsNumberOf = 0;

    Vector2 drawPosisiton = {0.0f,0.0f};
    float drawHeight = 0.0f;
    float shadowPower = 0.0f;
    Color wallColor = {0,0,0,255};

    for(int i = 1; i <= SCREEN_WIDTH; i++){
        wallsNumberOf = 0;

        raycasterCastRay(&rayLength,&tile, &side, startPosition, rayDirection, map, walls, &wallsNumberOf);
        
        for(int j = wallsNumberOf-1; j >= 0; j--){

            rayLength = walls[j].lenght;
            tile = walls[j].tile;
            side = walls[j].side;

            drawPosisiton.x = i;
            drawHeight = (SCREEN_HEIGHT / rayLength) * rendererConvertToWallSize(tile);
            drawPosisiton.y = (SCREEN_HEIGHT - drawHeight) / 2;

            if(side == VERTICAL){
                shadowPower = rayLength * SHADOW_POWER;
            }
            else if(side == HORIZONTAL) {
                shadowPower = rayLength * (SHADOW_POWER * 1.2);
            }
            wallColor = rendererConvertTileToColor(tile);
            wallColor = rendererDarkenColor(wallColor,shadowPower);

            DrawRectangleV(drawPosisiton, (Vector2){1,drawHeight}, wallColor);

            float rayAngleStepSize = playerFOV / SCREEN_WIDTH;
            rayAngle += rayAngleStepSize;
            rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};

        }
    }

}


void rendererDrawCelling(Color color){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2, color);
}

void rendererDrawFloor(Color color){
    DrawRectangle(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2, color);
}





#endif