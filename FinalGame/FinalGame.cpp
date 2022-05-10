#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"


bool isOnGround(int yPos, int windowHeight, int height)
{
    return yPos >= windowHeight - height;
}


int main(int argc, char* argv[])
{
    const int windowDimensions[2]{384,384};

    const float mapScale{4};
    
    InitWindow(windowDimensions[0],windowDimensions[1],"The final project!");

    Texture2D tileMap = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0,0};

    SetTargetFPS(60);

    Character knight{windowDimensions[0],windowDimensions[1]};
    enemy goblin{Vector2{600, 300},LoadTexture("characters/goblin_idle_spritesheet.png"),LoadTexture("characters/goblin_run_spritesheet.png")};

    Prop prop[2]{Prop{Vector2{600,300},LoadTexture("nature_tileset/Rock.png")},Prop{Vector2{400,500},LoadTexture("nature_tileset/Log.png")}};
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(),-1);

        //Draw map
        DrawTextureEx(tileMap,mapPos,0,mapScale,WHITE);

        //Draw props
        for (auto props : prop)
        {
            props.Render(knight.getWorldPos());
        }

        //Draw knight
        knight.tick(GetFrameTime());
        knight.keepCharacterInBound(knight,tileMap.width * mapScale,tileMap.height * mapScale,(float)windowDimensions[0],(float)windowDimensions[1]);
        for (auto props : prop)
        {
            if(CheckCollisionRecs(knight.getCollisionRect(),props.getCollisionRect(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }
        goblin.tick(GetFrameTime());
        
        EndDrawing();
    }

    knight.unloadTexture();
    for(auto props : prop)
    {
        props.unloadTexture();
    }
    UnloadTexture(tileMap);
    CloseWindow();
    
    return 0;
}
