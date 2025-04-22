#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

}

void BaseCharacter::undoMovements() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
    return Rectangle{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltaTime) {

    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        runningTime = 0.0;
        frame++;
        if (frame > maxFrames) frame = 0;
    }

    // Normalize direction checking if vector length is > 0 and add it to map position
    if (Vector2Length(velocity) != 0.0) {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = running;
    }
    else {
        texture = idle;
    }
    velocity = {};

    // draw character
    Rectangle source{frame * width, 0.0, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
    DrawTexturePro(texture, source, dest, {0.0, 0.0}, 0.0, WHITE);
}

Vector2 BaseCharacter::getScreenPos() {
    
};