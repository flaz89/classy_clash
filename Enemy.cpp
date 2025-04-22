#include "Enemy.h"
#include "raymath.h"

// constructor
Enemy::Enemy(Vector2 pos, Texture2D tex_idle, Texture2D tex_run) {
    worldPos = pos,
    texture = tex_idle,
    idle = tex_idle,
    running = tex_run,
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
};

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}

// tick
void Enemy::tick(float deltaTime) {

    if (!getAlive()) return;

    // get velocity to target
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())) {
        target->takeDamage(damageperSec * deltaTime);
    }
}



