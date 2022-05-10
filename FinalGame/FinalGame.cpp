#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"


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
    Prop rock{Vector2{},LoadTexture("nature_tileset/Rock.png")};

    Prop prop[2]{Prop{Vector2{600,300},LoadTexture("nature_tileset/Rock.png")},Prop{Vector2{400,500},LoadTexture("nature_tileset/Log.png")}};

    bool hasStarted{false};
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        if(!hasStarted)
        {
            //DrawText("Press W to start!", windowDimensions[0], windowDimensions[1], 5 , BLACK);
            if(IsKeyDown(KEY_W))
            {
                hasStarted = true;
            }
            knight.startFunction(windowDimensions[0],windowDimensions[1]);
        }
        else
        {
            mapPos = Vector2Scale(knight.getWorldPos(),-1);

            //Draw map
            DrawTextureEx(tileMap,mapPos,0,mapScale,WHITE);

            //Draw props
            for (auto props : prop)
            {
                props.Render(knight.getWorldPos());
            }

            //Draw
            knight.tick(GetFrameTime());
            knight.keepCharacterInBound(knight,tileMap.width * mapScale,tileMap.height * mapScale,(float)windowDimensions[0],(float)windowDimensions[1]);
            for (auto props : prop)
            {
                if(CheckCollisionRecs(knight.getCollisionRect(),props.getCollisionRect(knight.getWorldPos())))
                {
                    knight.undoMovement();
                }
            }
        }
        
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
