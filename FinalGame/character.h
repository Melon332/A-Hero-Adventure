#ifndef CHARACTER_H
#define CHARACTER_H


#include "BaseCharacter.h"
#include "raylib.h"
#include "raymath.h"

class Character : public base_character
{
public:
    Character(int winWidth, int winHeight);
    void tick(float deltaTime) override;
    Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRect() { return weaponCollisonRec; }
    float getDamage() const {return damage;}
    
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisonRec;
    float damage{20};
};
#endif