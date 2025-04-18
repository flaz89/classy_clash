#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) {
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) * 0.5f - (width * 0.5f) * scale,
        static_cast<float>(winHeight) * 0.5f - (height * 0.5f) * scale
    };
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y += 1.0;

    // Normalize direction checking if vector length is > 0 and add it to map position
    if (Vector2Length(direction) != 0.0) {
        Vector2 scaldeDirection = Vector2Scale(direction, speed);
        worldPos = Vector2Add(worldPos, scaldeDirection);
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = running;
    }
    else {
        texture = idle;
    }

    // update knight anim
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        runningTime = 0.0;
        frame++;
        if (frame > maxFrames) frame = 0;
    }

    // draw knight
    Rectangle source{frame * width, 0.0, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, width * scale, height * scale};
    DrawTexturePro(texture, source, dest, {0.0, 0.0}, 0.0, WHITE);
}

void Character::undoMovements() {
    worldPos = worldPosLastFrame;
}