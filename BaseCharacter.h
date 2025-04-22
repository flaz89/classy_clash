#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
private:

protected:
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D running{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D texture{idle};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: facing right, -1: facing left
    float rightLeft{-1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.0};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
    
public:
    BaseCharacter();
    Vector2 getWorldPos() { return this->worldPos; }
    virtual void tick(float deltaTime);
    void undoMovements();
    Rectangle getCollisionRec();
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return this->alive; };
    void setAlive(bool isAlive) { this->alive = isAlive; };

private:
    bool alive{true};
};

#endif
