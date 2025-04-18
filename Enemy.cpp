#include "Enemy.h"

// constructor
Enemy::Enemy(Vector2 pos, Texture2D tex_idle, Texture2D tex_run): 
worldPos(pos),
texture(tex_idle),
idle(tex_idle),
run(tex_run) {
    width = texture.width / maxFrames;
    height = texture.height;
};

// tick
void Enemy::tick(float deltaTime) {
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    // draw enemy
    Rectangle source{frame * width, 0.0, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, width * scale, height * scale};
    DrawTexturePro(texture, source, dest, {0.0, 0.0}, 0.0, WHITE);
}

// restor position of last frame
void Enemy::undoMovements() {
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec() {
    return Rectangle{screenPos.x, screenPos.y, width * scale, height * scale};
}