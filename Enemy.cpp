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
    if (!getAlive()) return;

    // Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    // Check length between enemy and target
    if (Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::Tick(deltaTime);

    // If enemy overlaps character, make character take damage
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::setTarget(Character* newTarget)
{
    target = newTarget;
}