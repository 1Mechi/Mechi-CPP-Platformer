#include "Platforms.h"

Platforms::Platforms(const char* staticSpriteLink ,const char* animationSpriteLink, Vector2 position)
{
    staticSprite = LoadTexture(staticSpriteLink);
    animationSprite = LoadTexture(animationSpriteLink);
    
    currentSprite = staticSprite;  
    pos = position;  
}

Platforms::~Platforms()
{
    UnloadTexture(staticSprite);
    UnloadTexture(animationSprite);
}

void Platforms::render()
{
    Rectangle src {0.0f , 0.0f, static_cast<float>(staticSprite.width), static_cast<float>(staticSprite.height)};
    Rectangle dest {pos.x , pos.y, src.width*scale, src.height*scale};
    Vector2 originVal{dest.width/2.0f, dest.height/2.0f};
    DrawTexturePro(currentSprite,src, dest, originVal,  0.0f, WHITE);

}

Rectangle Platforms::GetCollisionRec() const
{
    return Rectangle{
        pos.x - (staticSprite.width * scale / 2.0f),
        pos.y - (staticSprite.height * scale / 2.0f) + 10.0f,
        staticSprite.width * scale,
        staticSprite.height * scale
    };
}
