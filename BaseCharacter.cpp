#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    
    // Update animation frame
    runningTime += deltaTime;
    
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        
        if (frame > maxFrame) frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // Set world position to world position plus direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // Terniary operator for condition checks (if true : else false)
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }

    else
    {
        texture = idle;
    }

    velocity = {};
    
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
        
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};

    // Draw the character
    DrawTexturePro(texture, source, dest, Vector2Zero(), 0.0f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{ getScreenPos().x, getScreenPos().y, width * scale, height * scale };
}