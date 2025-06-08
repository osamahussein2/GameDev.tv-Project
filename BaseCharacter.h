#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }

    void undoMovement();
    Rectangle getCollisionRec();

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 screenPos{};
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
};

#endif