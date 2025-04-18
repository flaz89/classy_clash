#include "raylib.h"

class Character {
    public:
        Character(int winWidth, int winHeight);
        Vector2 getWorldPos() { return this->worldPos; }
        void tick(float deltaTime);
        void undoMovements();
    
    private:
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D running{LoadTexture("characters/knight_run_spritesheet.png")};
        Texture2D texture{idle};
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{0.0, 0.0};
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
    };