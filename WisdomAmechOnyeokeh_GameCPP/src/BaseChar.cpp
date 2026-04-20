#include "BaseChar.h"

BaseChar::BaseChar()
{
}

BaseChar::~BaseChar()
{
    UnloadTexture(idleSprite);
    UnloadTexture(runSprite);
}

void BaseChar::tick(float deltaTime, const Image& colMap, const float& mapScaleRef, const std::vector<Platforms>& platforms)
{
    Rectangle src {frameNum * width, 0.0f, rightLeft * width, height};
    Rectangle dest {pos.x, pos.y, width*scale, height*scale};
    Vector2 originVal{dest.width/2.0f, dest.height/2.0f};

    
    DrawTexturePro(currentSprite,src, dest, originVal,  0.0f, WHITE);
}

Vector2 BaseChar::getPos() const
{
    return {pos};
}
