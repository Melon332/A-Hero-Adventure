#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos;}
    void tick(float deltaTime);
    void startFunction(int windowWidth, int windowHeight);
    void keepCharacterInBound(Character character, float mapWidth, float mapHeight,float windowWidth, float windowHeight);
    void undoMovement();
    void unloadTexture();
    Rectangle getCollisionRect();
    
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
    const int maxFrame{6};
    int frame{0};
    const float speed {10};
    const float scale{4.0};
    float width{};
    float height{};
    Vector2 lastFrameWorldPos{};
};