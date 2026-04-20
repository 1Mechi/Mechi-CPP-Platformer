#pragma once
#include "raylib.h"

class Obstacle
{
private:
    Texture2D sprite{};
    Vector2 pos{};
    float width{};
    float height{};
    float scale{4.0f};
    int maxFrames{8};
    float runningTime{};
    float updateTime{1.0f / 12.0f};
    int frame{};
    
    bool isMovingSide{false};
    bool isMovingUp{false};

    float moveSpeed{100.0f};
    float moveRange{200.0f};

    int direction{1}; // right/up = 1, left/down = -1 

    Vector2 startPos{};
    
public:
    Obstacle(const char* , Vector2);
    ~Obstacle();
    void render(float);
    Rectangle getCollisionRec();
    void setMovingSide(bool moveState);
    void setMovingUp(bool moveState);
};

