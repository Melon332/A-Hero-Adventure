#include "character.h"

Character::Character()
{
    width = (float)currentTexture.width/maxFrame;
    height = currentTexture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth / 2.0f - 4.0f * (0.5f * width), (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}
void Character::tick(float deltaTime)
{
    Vector2 direction{0,0};
    if(IsKeyDown(KEY_A)) direction.x -= 1;
    if(IsKeyDown(KEY_D)) direction.x += 1;
    if(IsKeyDown(KEY_W)) direction.y -= 1;
    if(IsKeyDown(KEY_S)) direction.y += 1;

    lastFrameWorldPos = worldPos;

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
    Rectangle sourceRectKnight{width * frame,0, rightLeft * width ,height};
    Rectangle destRectKnight{screenPos.x,screenPos.y,width * scale, height * scale};

        
    DrawTexturePro(currentTexture,sourceRectKnight,destRectKnight,{0,0},0,WHITE);
}
void Character::startFunction(int width, int height)
{
    int measure = MeasureText("Press any key to start!",20);
    DrawText("Press W to start!", width / 2 - measure / 2.5f , height / 2, 20 , SKYBLUE);
}
void Character::keepCharacterInBound(Character character, float mapWidth, float mapHeight, float windowWidth, float windowHeight)
{
    if(character.getWorldPos().x < 0 ||
        character.getWorldPos().y < 0 ||
        character.getWorldPos().x + windowWidth > mapWidth ||
        character.getWorldPos().y + windowHeight > mapHeight)
    {
        undoMovement();
    } 
}
void Character::undoMovement()
{
    worldPos = lastFrameWorldPos;
}

