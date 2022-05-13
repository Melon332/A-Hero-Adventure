#include "Enemy.h"

#include <iostream>
#include <string>

enemy::enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex)
{
    width = (float)currentTexture.width/maxFrame;
    height = (float)currentTexture.height;
    rightLeft = 1;
    worldPos = pos;
    currentTexture = idleTex;
    idle = idleTex;
    run = runTex;
    speed = 2;
    health = 80;
}

void enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    //Get toTarget - Vector2 = Vector2Subtract(worldPos,target->getWorldPos());
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    if(Vector2Length(velocity) < radius) velocity = {};
    
    if(CheckCollisionRecs(target->getCollisionRect(),getCollisionRect()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
    
    base_character::tick(deltaTime);
    
    DrawRectangle(getScreenPos().x + offset.x - 15, getScreenPos().y + offset.y, 15 * healthBarScale, 5 * scale, RED);
}

Vector2 enemy::getScreenPos()
{
    return Vector2{Vector2Subtract(worldPos,target->getWorldPos())};
}
void enemy::takeDamage(float damage)
{
    base_character::takeDamage(damage);
    healthBarScale--;
}


