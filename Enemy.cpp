#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrame;
    height = texture.height;

    speed = 3.5f;
}

void Enemy::Tick(float deltaTime)
{
    // Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    BaseCharacter::Tick(deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::setTarget(Character* newTarget)
{
    target = newTarget;
}