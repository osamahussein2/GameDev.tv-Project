#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    
    virtual void Tick(float deltaTime) override;

private:
    
};