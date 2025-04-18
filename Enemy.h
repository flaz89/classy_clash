#include "raylib.h"

class Enemy {
private:
    Texture2D texture{idle};
    Texture2D idle{};
    Texture2D run{};
    Vector2 worldPos{};
    Vector2 screenPos{};
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
public:
    Enemy(Vector2 pos, Texture2D tex_idle, Texture2D tex_run);
    void tick(float deltaTime);
    Vector2 getWorldPos() {return this->worldPos;};
    void undoMovements();
    Rectangle getCollisionRec();
};

