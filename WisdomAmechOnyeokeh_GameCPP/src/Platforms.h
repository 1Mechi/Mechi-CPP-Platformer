#pragma once
#include "raylib.h"

class Platforms
{
private:
    Texture2D currentSprite{};
    Texture2D staticSprite {};
    Texture2D animationSprite{};
    float scale {5.0f};
    Vector2 pos{};
public:
    Platforms(const char*,const char* , Vector2);
    ~Platforms();
    void render();
    Rectangle GetCollisionRec() const;
};

