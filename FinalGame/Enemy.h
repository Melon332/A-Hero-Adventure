#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"
#include "character.h"

class enemy : public base_character
{
public:
    enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    void tick(float deltaTime) override;
    void setTarget(Character* player) {target = player;}
    Vector2 getScreenPos() override;
    void setWorldPos(Vector2 pos) { worldPos = pos;}
    void takeDamage(float damage) override;
private:
    Character* target;
    float damagePerSec{10.f};
    float radius{25.f};
    Vector2 offset{25, -10};
    float healthBarScale{4};
};
