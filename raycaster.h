#ifndef RAYCASTER_C
#define RAYCASTER_C

#include <math.h>
#include "constants.h"
#include "map.h"

void raycasterCastRay(float* length, TILE_TYPE* tile, SIDE* side, Vector2 startPosition, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]);

void raycasterCastRay(float* length, TILE_TYPE* tile, SIDE* side, Vector2 startPosition, Vector2 direction, TILE_TYPE map[MAP_HEIGHT][MAP_WIDTH]){

    Vector2 rayUnitStepSize = {
        sqrt(1+(direction.y / direction.x) * (direction.y / direction.x)),
        sqrt(1+(direction.x / direction.y) * (direction.x / direction.y))
        };

    Vector2 mapPositionCheck  = {startPosition.x,startPosition.y};

    Vector2 raylength = {0.0f,0.0f};

    Vector2 step = {0.0f,0.0f};

    if(direction.x < 0){
        step.x = -1;
        raylength.x = (startPosition.x - mapPositionCheck.x) * rayUnitStepSize.x;
    }
    else{
        step.x = 1;
        raylength.x = ((mapPositionCheck.x + 1) - startPosition.x) * rayUnitStepSize.x;
    }
    if(direction.y < 0){
        step.y = -1;
        raylength.y = (startPosition.y - mapPositionCheck.y) * rayUnitStepSize.y;
    }
    else{
        step.y = 1;
        raylength.y = ((mapPositionCheck.y + 1) - startPosition.y) * rayUnitStepSize.y;
    }

    bool tileFound = false;
    float maxDistance = 1000.0f;
    float distance = 0.0f;

    int axis = 0;

    while(!tileFound && distance < maxDistance){

        if(raylength.x < raylength.y){
            mapPositionCheck.x +=step.x;
            distance = raylength.x;
            raylength.x += rayUnitStepSize.x;
            axis = 0;
        }
        else{
            mapPositionCheck.y += step.y;
            distance = raylength.y;
            raylength.y += rayUnitStepSize.y; 
            axis = 1;            
        }

        if(mapGiveTileType(map,mapPositionCheck) != 0){
            tileFound = true;
            
            *tile = mapGiveTileType(map,mapPositionCheck);

            if(raylength.x <= raylength.y){
                *length = raylength.x;
                *side = (SIDE)axis;
            }else{
                *length = raylength.y;
                *side = (SIDE)axis;
            }  
        }
    }  
}



#endif