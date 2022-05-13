#include "BaseCharacter.h"

base_character::base_character()
{
    
}
void base_character::keepCharacterInBound(float mapWidth, float mapHeight, float windowWidth, float windowHeight)
{
    if(getWorldPos().x < 0 ||
    getWorldPos().y < 0 ||
    getWorldPos().x + windowWidth > mapWidth ||
    getWorldPos().y + windowHeight > mapHeight)
    {
        undoMovement();
    } 
}

void base_character::undoMovement()
{
    worldPos = lastFrameWorldPos;
}
void base_character::unloadTexture()
{
    UnloadTexture(currentTexture);
    UnloadTexture(run);
    UnloadTexture(idle);
}
Rectangle base_character::getCollisionRect()
{
    return Rectangle{getScreenPos().x,getScreenPos().y,width * scale,height * scale};
}
void base_character::tick(float deltaTime)
{
    if(Vector2Length(velocity) != 0.0)
    {
        currentTexture = run;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity),speed));
        velocity.x < 0.f ? rightLeft = -1 : rightLeft = 1;
    }
    else
    {
        currentTexture = idle;
    }
    
    velocity = {};


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
    Rectangle sourceRectCharacter{width * frame,0, rightLeft * width ,height};
    Rectangle destRectCharacter{getScreenPos().x,getScreenPos().y,width * scale, height * scale};

        
    DrawTexturePro(currentTexture,sourceRectCharacter,destRectCharacter,{0,0},0,WHITE);
}
void base_character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0)
    {
        setAlive(false);
    }
}


