#include "map.h"
#include "player.h"
#include "debug.h"
#include "renderer.h"



int main()
{

    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raycaster");

    SetTargetFPS(60);   

    Map map = mapCreate(); 
    Player player = playerCreate();

    bool isDebugMenuOn = false;

    while (!WindowShouldClose())    
    {

        playerMove(&player,map);
        playerRotate(&player); 
        playerChangeFOV();
        isDebugMenuOn = IsKeyDown(KEY_F3);
        
        BeginDrawing();

        ClearBackground(NEARBLACK);

        rendererDrawCelling(SKYBLUE);
        rendererDrawFloor(BEIGE);
        rendererDrawWallsSolidColor(player.position, player.angle, map.grid);

        if(isDebugMenuOn){
            debugDrawMiniMap(map.grid, player.position, player.direction);
            debugDrawPlayerInfo(player.position, player.direction, player.angle, map.grid);
            debugDrawPlayerRaySingle(player.position, player.direction, map.grid);

            //DrawFPS(10, 10);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}


