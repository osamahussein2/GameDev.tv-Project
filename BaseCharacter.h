#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }

    virtual void Tick(float deltaTime);

    void undoMovement();
    Rectangle getCollisionRec();

    virtual Vector2 getScreenPos() = 0;

    bool getAlive() {return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 worldPos{};

    // 1 is for facing right and -1 is for facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};

    float speed{4.f};

    float width{};
    float height{};

    Vector2 worldPosLastFrame{};

    float scale{4.0f};

    Vector2 velocity{};

private:
    bool alive{true};
};

#endif