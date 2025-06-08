#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    
    virtual void Tick(float deltaTime) override;

    virtual Vector2 getScreenPos() override;

private:
    int windowWidth{};
    int windowHeight{};
};

#endif