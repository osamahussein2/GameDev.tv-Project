#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    
    void Tick(float deltaTime);
    
private:
    
};