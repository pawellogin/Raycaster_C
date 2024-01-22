#include "map.h"
#include "player.h"
#include "debug.h"




int main()
{

    const int screenWidth = SCREEN_SMALL_WIDTH;
    const int screenHeight = SCREEN_SMALL_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);   



    Map map = mapCreate(); 
    Player player = playerCreate();


    while (!WindowShouldClose())    
    {

        playerMove(&player,map);
        playerRotate(&player); 
        

        BeginDrawing();

        ClearBackground(NEARBLACK);

        debugDrawMiniMap(map,player);
        debugDrawPlayerInfo(player,map);

        //DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}


