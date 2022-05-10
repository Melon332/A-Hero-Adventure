#include <iostream>

#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos;}
    void setScreenPos(int width, int height);
    void tick(float deltaTime);
    void startFunction(int width, int height);
private:
    //Texture variables
    Texture2D currentTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    //Animation variables
    float rightLeft{0.f};
    float runningTime{0.f};
    const float updateTime{1.f/12.f};
    const int maxFrame{5};
    int frame{0};
    const float speed {10};
    const float scale{4.0};
};

void Character::setScreenPos(int width, int height)
{
    screenPos = {(float)width / 2.0f - 4.0f * (0.5f * (float)currentTexture.width/6), (float)height / 2.0f - 4.0f * (0.5f * (float)currentTexture.height)};
}
void Character::tick(float deltaTime)
{
    Vector2 direction{0,0};
    if(IsKeyDown(KEY_A)) direction.x -= 1;
    if(IsKeyDown(KEY_D)) direction.x += 1;
    if(IsKeyDown(KEY_W)) direction.y -= 1;
    if(IsKeyDown(KEY_S)) direction.y += 1;

    if(Vector2Length(direction) != 0.0)
    {
        currentTexture = run;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction),speed));
        direction.x < 0.f ? rightLeft = -1 : rightLeft = 1;
    }
    else
    {
        currentTexture = idle;
    }

    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0;
        if(frame > maxFrame)
        {
            frame = 0;
        }
    }
    Rectangle sourceRectKnight{(float)currentTexture.width/6 * frame,0, rightLeft * (float)currentTexture.width/6,(float)currentTexture.height};
    Rectangle destRectKnight{screenPos.x,screenPos.y,(float)currentTexture.width/6 * scale,(float)currentTexture.height * scale};

        
    DrawTexturePro(currentTexture,sourceRectKnight,destRectKnight,{0,0},0,WHITE);
}
void Character::startFunction(int width, int height)
{
    int measure = MeasureText("Press any key to start!",20);
    DrawText("Press W to start!", width / 2 - measure / 2.5f , height / 2, 20 , SKYBLUE);
}


bool isOnGround(int yPos, int windowHeight, int height)
{
    return yPos >= windowHeight - height;
}


int main(int argc, char* argv[])
{
    const int windowDimensions[2]{384,384};
    
    InitWindow(windowDimensions[0],windowDimensions[1],"The final project!");

    Texture2D tileMap = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0,0};

    SetTargetFPS(60);

    Character knight{};

    knight.setScreenPos(windowDimensions[0],windowDimensions[1]);

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
        
            DrawTextureEx(tileMap,mapPos,0,4,WHITE);

            knight.tick(GetFrameTime());
        }
        
        EndDrawing();
    }
    
    UnloadTexture(tileMap);
    CloseWindow();
    
    return 0;
}
