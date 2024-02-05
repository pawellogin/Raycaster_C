#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "constants.h"
#include "structures.h"
#include "map.h"
#include <math.h>
#include <stdio.h>


typedef struct Player_t {
    Vector2 position;
    Vector2 direction;
    float angle;
}Player;

Player playerCreate();

void playerMove(Player * player,Map map);
void playerRotate(Player* player);
void playerChangeFOV();

float playerFOV = 60 * DEG2RAD;

Player playerCreate(){
    return(Player){
        .position.x = 3,
        .position.y = 3.65f,
        .direction.x = 0,
        .direction.y = 0,
        .angle = 60 * DEG2RAD
    };
}



void playerMove(Player * player, Map map){

    Vector2 newPosition;


    if(IsKeyDown(KEY_W)){
        
        newPosition.x = player->position.x + player->direction.x * PLAYER_MOVEMENT_SPEED;
        newPosition.y = player->position.y + player->direction.y * PLAYER_MOVEMENT_SPEED;

        if(mapGiveTileType(map.grid,newPosition) == EMPTY){
            player->position.x = newPosition.x;
            player->position.y = newPosition.y; 
        }
        
    }else if(IsKeyDown(KEY_S)){
        newPosition.x = player->position.x - player->direction.x * PLAYER_MOVEMENT_SPEED;
        newPosition.y = player->position.y - player->direction.y * PLAYER_MOVEMENT_SPEED;
        
        if(mapGiveTileType(map.grid,newPosition) == EMPTY){
            player->position.x = newPosition.x;
            player->position.y = newPosition.y; 
        }
    }

    if(IsKeyDown(KEY_A)){
        newPosition.x = player->position.x + cos(player->angle - 90 * DEG2RAD) * PLAYER_MOVEMENT_SPEED;
        newPosition.y = player->position.y + sin(player->angle - 90 * DEG2RAD) * PLAYER_MOVEMENT_SPEED;
        
        if(mapGiveTileType(map.grid,newPosition) == EMPTY){
            player->position.x = newPosition.x;
            player->position.y = newPosition.y; 
        }
    }else if(IsKeyDown(KEY_D)){
        newPosition.x = player->position.x + cos(player->angle + 90 * DEG2RAD) * PLAYER_MOVEMENT_SPEED;
        newPosition.y = player->position.y + sin(player->angle + 90 * DEG2RAD) * PLAYER_MOVEMENT_SPEED;
        
        if(mapGiveTileType(map.grid,newPosition) == EMPTY){
            player->position.x = newPosition.x;
            player->position.y = newPosition.y; 
        }
    }
    }

void playerRotate(Player* player) {
    if(IsKeyDown(KEY_LEFT)){
        player->angle -= PLAYER_ROTATION_SPEED;
    }else if (IsKeyDown(KEY_RIGHT)){
        player->angle += PLAYER_ROTATION_SPEED;
    }

    if(player->angle > 360 * DEG2RAD){
        player->angle = 0;
    }
    else if(player->angle < 0){
        player->angle = 360 * DEG2RAD;
    }

    player->direction.x = cos(player->angle);
    player->direction.y = sin(player->angle);
}

void playerChangeFOV(){
    const float changeSpeed = 0.05f; 
    if(IsKeyDown(KEY_EQUAL) && playerFOV < 180 * DEG2RAD){
        playerFOV += changeSpeed;
    } else if(IsKeyDown(KEY_MINUS) && playerFOV > 15 * DEG2RAD){
        playerFOV -= changeSpeed;
    }
}





#endif