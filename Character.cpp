#include "Character.h"

Character::Character()
{
    width = texture.width / maxFrame;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth / 2.0f - 4.0f * (0.5f * width),
                 (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

void Character::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // Set world position to world position plus direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        // Terniary operator for condition checks (if true : else false)
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }

    else
    {
        texture = idle;
    }

    // Update animation frame
    runningTime += deltaTime;
    
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        
        if (frame > maxFrame) frame = 0;
    }
    
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
        
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};

    // Draw the character
    DrawTexturePro(texture, source, dest, Vector2Zero(), 0.0f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}