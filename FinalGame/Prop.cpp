#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : texture(tex), worldPos(pos)
{
    
}
void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture,screenPos,0,scale,WHITE);
}
void Prop::unloadTexture()
{
    UnloadTexture(texture);
}
Rectangle Prop::getCollisionRect(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    return Rectangle{screenPos.x,screenPos.y,static_cast<float>(texture.width) * scale,static_cast<float>(texture.height) * scale};
}



