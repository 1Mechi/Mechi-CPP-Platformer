#include "Obstacle.h"

Obstacle::Obstacle(const char * animpath, Vector2 position)
{
    sprite = LoadTexture(animpath);

    pos = position;
    startPos = position;
    width = static_cast<float>(sprite.width) / maxFrames;
    height = static_cast<float>(sprite.height);
}

Obstacle::~Obstacle()
{
    UnloadTexture(sprite);
}

void Obstacle::render(float deltaTime)
{
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;

        if (frame >= maxFrames)
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


    if (isMovingSide){
        pos.x += direction * moveSpeed * deltaTime;

        float distance = pos.x - startPos.x;

        if (distance > moveRange)
        {
            direction = -1;
        }
        else if (distance < -moveRange)
        {
            direction = 1;
        }
    }
    
    if (isMovingUp){
        pos.y += direction * moveSpeed * deltaTime;

        float distance = pos.y - startPos.y;

        if (distance > moveRange)
        {
            direction = -1;
        }
        else if (distance < -moveRange)
        {
            direction = 1;
        }
    }
    
    DrawTexturePro(sprite, src, dest, origin, 0.0f, WHITE);

}

Rectangle Obstacle::getCollisionRec()
{
    return Rectangle{
        pos.x - (width * scale / 2.0f),
        pos.y - (height * scale / 2.0f),
        width * scale,
        height * scale
    };
}

void Obstacle::setMovingSide(bool moveState)
{
    isMovingSide = moveState;
}

void Obstacle::setMovingUp(bool moveState)
{
    isMovingUp = moveState;
}
