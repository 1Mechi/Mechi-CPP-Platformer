#include "Collectible.h"

Collectible::Collectible(const char *texturePath, Vector2 position)
{
    sprite = LoadTexture(texturePath);
    pos = position;

    width = static_cast<float>(sprite.width) / maxFrames;
    height = static_cast<float>(sprite.height);
}

Collectible::~Collectible()
{
    UnloadTexture(sprite);
}

void Collectible::render(float deltaTime) 
{
    if (isHit) return;

    // animation update
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;

        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    Rectangle src{
        frame * width,
        0.0f,
        width,
        height
    };

    Rectangle dest{
        pos.x,
        pos.y,
        width * scale,
        height * scale
    };

    Vector2 origin{
        dest.width / 2.0f,
        dest.height / 2.0f
    };

    DrawTexturePro(sprite, src, dest, origin, 0.0f, WHITE);
}

Rectangle Collectible::getCollisionRec() 
{
    return Rectangle{
        pos.x - (width * scale / 2.0f),
        pos.y - (height * scale / 2.0f),
        width * scale,
        height * scale
    };
}

bool Collectible::getIsHit() const
{
    return isHit;
}

void Collectible::setHitState(bool hitState)
{
    isHit = hitState;
}


