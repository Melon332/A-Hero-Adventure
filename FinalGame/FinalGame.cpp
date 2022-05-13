#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


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
    enemy goblin{Vector2{800, 300},LoadTexture("characters/goblin_idle_spritesheet.png"),LoadTexture("characters/goblin_run_spritesheet.png")};
    enemy slime{Vector2{800, 900},LoadTexture("characters/slime_idle_spritesheet.png"),LoadTexture("characters/slime_run_spritesheet.png")};
    enemy slime2{Vector2{400, 300},LoadTexture("characters/slime_idle_spritesheet.png"),LoadTexture("characters/slime_run_spritesheet.png")};
    enemy* enemies[3]
    {
        &goblin,
        &slime,
        &slime2
    };

    Rectangle screen {0.f,0.f, static_cast<float>(windowDimensions[0] + 25),static_cast<float>(windowDimensions[1] + 25)};
    
    Prop prop[2]{Prop{Vector2{600,300},LoadTexture("nature_tileset/Rock.png")},Prop{Vector2{400,500},LoadTexture("nature_tileset/Log.png")}};
    
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }
    
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
        knight.keepCharacterInBound(tileMap.width * mapScale,tileMap.height * mapScale,(float)windowDimensions[0],(float)windowDimensions[1]);
        for (auto props : prop)
        {
            if(CheckCollisionRecs(knight.getCollisionRect(),props.getCollisionRect(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        if(!knight.getAlive()) // is not alive
        {
            int measure = MeasureText("Game Over!", 40);
            DrawText("Game Over!", windowDimensions[0] / 2 - measure / 2, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
            std::string health = "Health: ";
            health.append(std::to_string(knight.getHealth()),0,5);
            DrawText(health.c_str(),0,0,40,WHITE);

        for (auto enemy : enemies)
        {
            if(CheckCollisionRecs(enemy->getCollisionRect(),screen))
            {
                enemy->tick(GetFrameTime());
            }
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if(CheckCollisionRecs(knight.getWeaponCollisionRect(),enemy->getCollisionRect()))
                {
                    enemy->takeDamage(knight.getDamage());
                }
            }
        }
        
        EndDrawing();
    }

    knight.unloadTexture();
    prop[0].unloadTexture();
    UnloadTexture(tileMap);
    CloseWindow();
    
    return 0;
}
