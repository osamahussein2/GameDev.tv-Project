#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrame;
    height = texture.height;
}

void Enemy::Tick(float deltaTime)
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