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
    
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
        
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};

    // Draw the character
    DrawTexturePro(texture, source, dest, Vector2Zero(), 0.0f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{ screenPos.x, screenPos.y, width * scale, height * scale };
}