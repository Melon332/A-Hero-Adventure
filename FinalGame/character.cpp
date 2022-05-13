#include "character.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth), windowHeight(winHeight)
{
    width = (float)currentTexture.width/maxFrame;
    height = (float)currentTexture.height;
    rightLeft = 1;
}
Vector2 Character::getScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width), static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}


void Character::tick(float deltaTime)
{
    if(!getAlive()) return;
    if(IsKeyDown(KEY_A)) velocity.x -= 1;
    if(IsKeyDown(KEY_D)) velocity.x += 1;
    if(IsKeyDown(KEY_W)) velocity.y -= 1;
    if(IsKeyDown(KEY_S)) velocity.y += 1;

    lastFrameWorldPos = worldPos;

    base_character::tick(deltaTime);

    //Draw sword
    Vector2 origin{};
    Vector2 offset{};
    float rotation;
    if(rightLeft > 0)
    {
        origin = {0.f,weapon.height * scale};
        offset = {35.f,55.f};
        weaponCollisonRec = {getScreenPos().x + offset.x, getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};
        rotation = 35.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f,55.f};
        weaponCollisonRec = {getScreenPos().x + offset.x - weapon.width * scale, getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};
        rotation = -35.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0;
    }

    Rectangle swordSource{0,0,static_cast<float>(weapon.width) * rightLeft,static_cast<float>(weapon.height)};
    Rectangle swordDest{getScreenPos().x + offset.x,getScreenPos().y + offset.y ,weapon.width * scale, weapon.height * scale};
    
    DrawTexturePro(weapon,swordSource,swordDest,origin,rotation,WHITE);
    DrawRectangleLines(0,0,windowWidth,windowHeight,RED);
}



