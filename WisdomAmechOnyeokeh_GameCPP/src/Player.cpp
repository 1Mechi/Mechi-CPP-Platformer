#include "Player.h"



Player::Player(Vector2 Position)
{
    currentSprite = idleSprite = LoadTexture("assets/textures/characters/frog/Idle (32x32).png");
    runSprite = LoadTexture("assets/textures/characters/frog/Run (32x32).png");
    jumpStartSprite = LoadTexture("assets/textures/characters/frog/Jump (32x32).png");
    jumpEndSprite = LoadTexture("assets/textures/characters/frog/Fall (32x32).png");
    pos = Position;
    speed = 500.0f;
    width = static_cast<float>(currentSprite.width)/maxFrames;
    height = static_cast<float>(currentSprite.height);
    resetLifeVal = life;
}


void Player::tick(float deltaTime, const Image& colMap, const float& mapScaleRef, const std::vector<Platforms>& platforms)
{
    lastPos = pos;
    // isOnGround = false;
    isMoving = false;
    runningTime += deltaTime;

    // Check alive
    if(!isAlive){
        return;
    }
    // animation time
    if (runningTime >= updateTime){
        runningTime = 0.0f;
        frameNum++;
        if(frameNum > maxFrames) {
            frameNum = 0;
        }
    }

    // jump input
    if (jumpInput() && isOnGround){
        velocityY = jumpVel;
        isOnGround = false;
    }

    // movemnet
    Vector2 nextPos = pos;

    velocityY += gravity * deltaTime;
    nextPos.y += velocityY * deltaTime;

    // Direction (up/down)
    int upDown = (velocityY < 0) ? -1 : 1;

    // VERTICAL MOVEMENT
    Vector2 verticalCheck;

    if (upDown > 0) // falling
    {
        verticalCheck = {
            nextPos.x,
            nextPos.y + (height * scale / 2.0f)
        };

        if (canMove(verticalCheck, colMap, mapScaleRef))
        {
            pos.y = nextPos.y;
            isOnGround = false;
        }
        else
        {
            velocityY = 0;
            isOnGround = true;
        }
    }
    else // jumping up
    {
        verticalCheck = {
            nextPos.x,
            nextPos.y - height
        };

        if (canMove(verticalCheck, colMap, mapScaleRef))
        {
            pos.y = nextPos.y;
        }
        else
        {
            velocityY = 0;
            // nextPos.y = pos.y; // cancel up movement
        }
    }

    // Check platform collision
    if (velocityY > 0) 
    {
        for (auto& p : platforms) 
        {
            Rectangle pRec = p.GetCollisionRec();
            float pTop = pRec.y;
            
            float playerBottom = pos.y + (height * scale / 2.0f);
            float lastPlayerBottom = lastPos.y + (height * scale / 2.0f);

            // Check over platfomr top
            if (lastPlayerBottom <= pTop && playerBottom >= pTop) 
            {
                if (pos.x >= pRec.x && pos.x <= (pRec.x + pRec.width)) 
                {
                    pos.y = pTop - (height * scale / 2.0f);
                    velocityY = 0;
                    isOnGround = true;
                }
            }
        }
    }
    // HORIZONTAL MOVEMENT 
    if(moveRight()) {
        nextPos.x += speed * deltaTime;
        rightLeft = 1;
        isMoving = true;
    }
    if(moveLeft()) {
        nextPos.x -= speed * deltaTime;
        rightLeft = -1;
        isMoving = true;
    }

    Vector2 basePos = {
        nextPos.x + (rightLeft * width),
        pos.y + (height * scale / 2.0f)
    };

    if (canMove(basePos, colMap , mapScaleRef))
    {
        pos.x = nextPos.x;
    }
    else
    {
        // fix irregular floor collisions
        const float stepHeight = 5.0f;

        Vector2 stepCheck = {
            basePos.x,
            basePos.y - stepHeight
        };

        if (canMove(stepCheck, colMap, mapScaleRef))
        {
            pos.x = nextPos.x;
            pos.y -= stepHeight;
        }
    }

    // -------- DEBUG --------
    // DrawCircleV(pos, 12, GREEN);   
    // DrawCircleV(verticalCheck, 50, RED); // updown check
    // DrawCircleV(basePos, 10, BLUE);      // leftright check

    // animation sprites
    if (!isOnGround){
        maxFrames = 1;
        updateTime = 1.0f;
        if (velocityY < 0){
            currentSprite = jumpStartSprite;
        }else{
            currentSprite = jumpEndSprite;
        }
    }
    else if(isMoving){
        maxFrames = 11;
        updateTime = 1.0f / 24.0f;
        currentSprite = runSprite;
    }
    else{
        maxFrames = 10;
        updateTime = 1.0f / 18.0f;
        currentSprite = idleSprite;
    }

    
    BaseChar::tick(deltaTime, colMap, mapScaleRef, platforms);
}

void Player::addFruit()
{
    fruitCount++;
}

int Player::getFruitCount() const
{
    return fruitCount;
}

Rectangle Player::getCollisionRec() const
{
    return Rectangle{
        pos.x - (width * scale / 2.0f),
        pos.y - (height * scale / 2.0f),
        width * scale,
        height * scale
    };
}

int Player::getLife() const
{
    return life;
}

void Player::reduceHealth()
{
    if (life < 1){
        isAlive = false;
    }
    else{
        life--;
    }
}

void Player::reset(Vector2 startPos){
    pos = startPos;
    lastPos = startPos;

    velocityY = 0;
    isOnGround = false;
    life = resetLifeVal;
    rightLeft = 1;
    isMoving = false;
    fruitCount = 0;
}

bool Player::canMove(Vector2 position, const Image& collisionMap, float scale)const
{
    // Adjust for map rescale
    int pixelX = static_cast<int>(position.x / scale);
    int pixelY = static_cast<int>(position.y / scale);

    // Check pixel val
    Color pixelVal = GetImageColor(collisionMap,pixelX,pixelY);

    return (pixelVal.r > 220);
}

bool Player::moveRight()const{
    return IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
}

bool Player::moveLeft() const{
    return IsKeyDown(KEY_LEFT)|| IsKeyDown(KEY_A) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_LEFT);
}

bool Player::jumpInput() const
{
    return IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || 
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
}
