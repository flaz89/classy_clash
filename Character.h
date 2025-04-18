#include "raylib.h"

class Character {
    public:
        Character();
        Vector2 getWorldPos() { return this->worldPos; }
        void setScreenPos(int winWidth, int winHeight);
        void tick(float deltaTime);
    
    private:
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D running{LoadTexture("characters/knight_run_spritesheet.png")};
        Texture2D texture{idle};
        Vector2 screenPos{};
        Vector2 worldPos{};
        // 1: facing right, -1: facing left
        float rightLeft{-1.f};
        // Animation variables
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.f / 12.f};
        float speed{4.f};
        float width{};
        float height{};
    };