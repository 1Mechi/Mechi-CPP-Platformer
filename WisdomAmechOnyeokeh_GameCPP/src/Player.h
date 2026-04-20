#pragma once
#include "BaseChar.h"


class Player : public BaseChar{
    public:
        Player(Vector2 );
        void tick( float deltaTime, const Image& colMap, const float& mapScaleRef, const std::vector<Platforms>& platforms) override;
        void addFruit();
        int getFruitCount() const;
        Rectangle getCollisionRec() const;
        int getLife()const;
        void reduceHealth();
        bool isReceivingDamage{false};
        void reset(Vector2);
        
    private:
        bool canMove(Vector2 mapPos, const Image& collisionMap, float scale)const;
        bool moveRight() const;
        bool moveLeft() const;
        bool jumpInput() const;
        Vector2 lastPos{};
        int life{3};
        int resetLifeVal{};
        int fruitCount{};
        bool isAlive{true};

        
    protected:
};