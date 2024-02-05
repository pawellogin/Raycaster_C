#ifndef DEBUG_H
#define DEBUG_H

#include "raylib.h"
#include "raymath.h"
#include "constants.h"
#include "structures.h"
#include "raycaster.h"
#include "renderer.h"
#include <math.h>


void debugDrawMiniMap(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void debugDrawPlayerOnMiniMap(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void debugDrawInfo(Vector2 position, Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);
Vector2 debugConvertToMinimapSize(Vector2 positionToConvert);

void debugDrawMiniMap(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){

    Color tileColor = BLANK;

    for(int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j< MAP_WIDTH;j++){
            switch(map[i][j]){
                case EMPTY:
                tileColor = RAYWHITE;
                break;
                
                default:
                tileColor = rendererConvertTileToColor(map[i][j]);
            }
            DrawRectangle(i*MINIMAP_SCALE + MINIMAP_OFFSET_X,j*MINIMAP_SCALE,MINIMAP_SCALE-1,MINIMAP_SCALE-1,tileColor);          
        }
    }

}

void debugDrawPlayerOnMiniMap(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    position.x = position.x * MINIMAP_SCALE;
    position.x += MINIMAP_OFFSET_X;
    
    position.y = position.y * MINIMAP_SCALE;
    

    DrawCircleV(position,0.3*MINIMAP_SCALE,RED);

    Vector2 lineEnd = {position.x + MINIMAP_SCALE * direction.x, position.y + MINIMAP_SCALE * direction.y,};

    DrawLineEx(position,lineEnd,2,TEXT_COLOR);
}

void debugDrawInfo(Vector2 position,Vector2 direction, float angle,TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    Vector2 drawPos = {
        10,
        10
    };
    int fontSize = 20;
    float textSpacing = 20;
    int textNumber = 0;

    char fpsText[20];
    snprintf(fpsText,sizeof(fpsText),"Fps: = %d", GetFPS());
    DrawText(fpsText, drawPos.x,drawPos.y + (textSpacing * textNumber), fontSize, TEXT_COLOR);
    textNumber++;

    char positionText[40];
    snprintf(positionText,sizeof(positionText),"Position: X = %.2f Y = %.2f",position.x, position.y);
    DrawText(positionText, drawPos.x, drawPos.y + (textSpacing * textNumber), fontSize,TEXT_COLOR);
    textNumber++;

    char angleText[40];
    snprintf(angleText,sizeof(angleText),"Angle: %.2f",angle * RAD2DEG);
    DrawText(angleText,drawPos.x, drawPos.y + (textSpacing * textNumber), fontSize,TEXT_COLOR);
    textNumber++;

    char singleRaylength[40];
    size_t arS = 0;
    TileToDraw* tileArray = NULL;

    tileArray = raycasterCastRay(position, direction, map, &arS);
    snprintf(singleRaylength,sizeof(singleRaylength),"Single ray length: %.2f",tileArray[0].rayLength);
    DrawText(singleRaylength,drawPos.x ,drawPos.y + (textSpacing * textNumber), fontSize,TEXT_COLOR);
    textNumber++;

    char currentTileText[40];
    TILE_TYPE tileType = (TILE_TYPE)tileArray[0].tile;
    snprintf(currentTileText, sizeof(currentTileText), "Pointing at tile: %s", tileTypeToString(tileType));
    DrawText(currentTileText, drawPos.x, drawPos.y + (textSpacing * textNumber), fontSize, TEXT_COLOR);
    textNumber++;

    if(tileArray != NULL){
        free(tileArray);
    }

}

void debugDrawPlayerRaySingle(Vector2 position, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){

    size_t arraySize = 0;
    TileToDraw* tileArray = NULL;
    Vector2 drawStartPosition = debugConvertToMinimapSize(position);
    Vector2 drawEndPosition = {0.0f, 0.0f};

    tileArray = raycasterCastRay(position, direction, map, &arraySize);

    for(size_t i = arraySize - 1; i != SIZE_MAX; i --){

        drawEndPosition.x = position.x + tileArray[i].rayLength * direction.x;
        drawEndPosition.y = position.y + tileArray[i].rayLength * direction.y;

        drawEndPosition = debugConvertToMinimapSize(drawEndPosition);

        DrawLineEx(drawStartPosition,drawEndPosition,3,RED);
    }   


    if(tileArray != NULL){
        free(tileArray);
    }
}

void debugDrawPlayerRayMulti(Vector2 startPosition, float startAngle, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){
    float rayAngle = startAngle - playerFOV/2;
    Vector2 rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};
    size_t arraySize = 0;
    TileToDraw* tileArray = NULL;
    Vector2 drawStartPosition = debugConvertToMinimapSize(startPosition);
    Vector2 drawEndPosition = {0.0f, 0.0f};

    Color rayColor = RED;
    
    for(size_t i = 1; i <= SCREEN_WIDTH; i++){
        tileArray = raycasterCastRay(startPosition, rayDirection, map, &arraySize);
        rayColor = RED;
        
        for(size_t j = arraySize - 1; j != SIZE_MAX; j --){
            rayColor.a = (unsigned char)(j+1)*2;
            drawEndPosition.x = startPosition.x + tileArray[j].rayLength * rayDirection.x;
            drawEndPosition.y = startPosition.y + tileArray[j].rayLength * rayDirection.y;

            drawEndPosition = debugConvertToMinimapSize(drawEndPosition);

            DrawLineEx(drawStartPosition,drawEndPosition,1,rayColor);
        }  

        if(tileArray != NULL){
            free(tileArray);
        } 

        float rayAngleStepSize = playerFOV / SCREEN_WIDTH;
        rayAngle += rayAngleStepSize;
        rayDirection = (Vector2){cos(rayAngle),sin(rayAngle)};
    }

}

Vector2 debugConvertToMinimapSize(Vector2 positionToConvert){
    positionToConvert.x = (positionToConvert.x) * MINIMAP_SCALE ;
    positionToConvert.x += MINIMAP_OFFSET_X;

    positionToConvert.y = (positionToConvert.y) * MINIMAP_SCALE;
    positionToConvert.y += MINIMAP_OFFSET_Y;

    return positionToConvert;
}



#endif
