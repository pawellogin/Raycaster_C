#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"
#include "constants.h"
#include "raycaster.h"
#include <math.h>

Color rendererConvertTileToColor(TILE_TYPE tile);
Color rendererDarkenColor(Color color, float shadowPower);
Color rendererChangeToNearblack(Color darkColor);
float rendererConvertToWallSize(TILE_TYPE tile);
void rendererDrawWalls(Vector2 startPosition, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);

Color rendererConvertTileToColor(TILE_TYPE tile){
    switch (tile)
    {
    case SOLID:
        return LIGHTGRAY;
        break;
    
    default:
        return RED;
        break;
    }
}

Color rendererDarkenColor(Color color, float shadowPower) {
    if(shadowPower > 1) color = NEARBLACK;
    else{
        float shadow = color.r * shadowPower;
        color.r -= shadow;

        shadow = color.g * shadowPower;
        color.g -= shadow;

        shadow = color.b * shadowPower;
        color.b -= shadow;

        color = rendererChangeToNearblack(color);

    }

    return color;
}

Color rendererChangeToNearblack(Color darkColor){
    Color nearblack = darkColor;
    if(darkColor.r < NEARBLACK.r) nearblack.r = NEARBLACK.r;
    if(darkColor.g < NEARBLACK.g) nearblack.g = NEARBLACK.g;
    if(darkColor.b < NEARBLACK.b) nearblack.b = NEARBLACK.b;

    return nearblack;
}

float rendererConvertToWallSize(TILE_TYPE tile){
    switch (tile)
    {
    case EMPTY:
        return 0.0f;
        break;

    case SOLID: 
        return 50.0f;

    default:
        return 0.0f;
        break;
    }
}

void rendererDrawWalls(Vector2 startPosition, float startAngle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    float rayAngle = startAngle - PLAYER_POV/2;
    Vector2 rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};
    float rayLength = 0;

    TILE_TYPE tile = EMPTY;
    SIDE side = VERTICAL;

    Vector2 drawPosisiton = {0.0f,0.0f};
    float drawHeight = 0.0f;
    float shadowPower = 0.0f;
    Color wallColor = {0,0,0,255};


    for(size_t i = 0; i < SCREEN_WIDTH; i++){
        raycasterCastRay(&rayLength,&tile, &side, startPosition, rayDirection, map);
        
        drawPosisiton.x = i;
        drawPosisiton.y = (SCREEN_HEIGHT - drawHeight) / 2;

        drawHeight = (SCREEN_HEIGHT / rayLength) * rendererConvertToWallSize(tile);

        if(side == VERTICAL){
            shadowPower = rayLength * SHADOW_POWER;
        }
        else if(side == HORIZONTAL) {
            shadowPower = rayLength * (SHADOW_POWER * 1.2);
        }
        wallColor = rendererConvertTileToColor(tile);
        wallColor = rendererDarkenColor(wallColor,shadowPower);

        DrawRectangleV(drawPosisiton, (Vector2){1,drawHeight}, wallColor);

        float rayAngleStepSize = PLAYER_POV / SCREEN_WIDTH;
        rayAngle += rayAngleStepSize;
        rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};
    }

}





#endif