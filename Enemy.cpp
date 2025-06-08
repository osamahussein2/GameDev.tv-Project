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
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::Tick(deltaTime);
}

void Enemy::setTarget(Character* newTarget)
{
    target = newTarget;
}