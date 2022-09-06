#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
    worldPos(pos),
    texture(tex)
{

};

void Prop::Render(Vector2 warPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, warPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop:: getCollisionRec(Vector2 warPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, warPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}