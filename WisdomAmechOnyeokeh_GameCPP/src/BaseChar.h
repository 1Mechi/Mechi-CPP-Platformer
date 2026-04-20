#pragma once
#include "raylib.h"
#include <vector>
#include "Platforms.h"


class BaseChar
{
private:
    /* data */
public:
    BaseChar();
    ~BaseChar();
    virtual void  tick(float deltaTime, const Image& colMap, const float& mapScaleRef, const std::vector<Platforms>& platforms);
    Vector2 getPos() const;

protected:
    Texture2D currentSprite {};
    Texture2D idleSprite {};
    Texture2D runSprite {};
    Texture2D jumpStartSprite{};
    Texture2D jumpEndSprite{};
    int maxFrames{11};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 pos{};
    float speed {40.0f};
    int rightLeft{1};
    bool isMoving{false};
    int frameNum{};
    float runningTime{};
    float updateTime{1.0f / 18.0f};
    float velocityY{};
    float gravity{1000.0f};
    float jumpVel{-800.0f};
    bool isOnGround{true};
    
    
    
};
