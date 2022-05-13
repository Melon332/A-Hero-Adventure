#pragma once
#ifndef BASE_CHARACTER_H
#include "raylib.h"
#include "raymath.h"

#define BASE_CHARACTER_H

class base_character
{
public:
    base_character();
    Vector2 getWorldPos() { return worldPos;}
    virtual Vector2 getScreenPos() = 0;
    void undoMovement();
    void unloadTexture();
    Rectangle getCollisionRect();
    virtual void tick(float deltaTime);
    void keepCharacterInBound(float mapWidth, float mapHeight,float windowWidth, float windowHeight);
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) { alive = isAlive;}
    float getHealth() const {return health; }
    virtual void takeDamage(float damage);
protected:
    //Texture variables
    Texture2D currentTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    //Animation variables
    float rightLeft{0.f};
    float runningTime{0.f};
    const float updateTime{1.f/12.f};
    const int maxFrame{6};
    int frame{0};
    float speed {10};
    const float scale{4.0};
    float width{};
    float height{};
    Vector2 lastFrameWorldPos{};
    Vector2 velocity{};
    float health{100};
private:
    bool alive{true};
    
};

#endif