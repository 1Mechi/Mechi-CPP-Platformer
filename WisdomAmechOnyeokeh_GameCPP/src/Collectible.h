#pragma once
#include "raylib.h"

class Collectible
{
private:
    Texture2D sprite{};
    Vector2 pos{};
    float scale{4.0f};
    bool isHit{false};
    float runningTime{0.0f};
    float updateTime{1.0f / 12.0f}; 
    int frame{0};
    int maxFrames{17};
    float width{};
    float height{};
public:
    Collectible(const char* , Vector2 );
    ~Collectible();

    void render(float deltaTime);
    Rectangle getCollisionRec() ;

    bool getIsHit() const ;
    void setHitState(bool) ;

};


