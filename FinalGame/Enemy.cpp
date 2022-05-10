#include "Enemy.h"
#include <iostream>

enemy::enemy(Vector2 pos, Texture2D idle, Texture2D run) : worldPos(pos), idle(idle), run(run),currentTexture(idle)
{
    width = (float)currentTexture.width/maxFrame;
    height = (float)currentTexture.height;
    rightLeft = 1;
}
void enemy::tick(float deltaTime)
{
    lastFrameWorldPos = worldPos;

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
    Rectangle sourceEnemyRect{width * frame,0, rightLeft * width ,height};
    Rectangle destEnemyRect{screenPos.x,screenPos.y,width * scale, height * scale};
        
    DrawTexturePro(currentTexture,sourceEnemyRect,destEnemyRect,{0,0},0,WHITE);
}
void enemy::undoMovement()
{
    worldPos = lastFrameWorldPos;
}

Rectangle enemy::getCollisionRect()
{
    return Rectangle{screenPos.x,screenPos.y,width * scale,height * scale};
}

