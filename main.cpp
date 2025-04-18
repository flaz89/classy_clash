#include "raylib.h"
#include "raymath.h"
#include <iostream>

class Character
{
public:
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
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth * 0.5f - ((float)texture.width * 0.5f / 6.0f) * 4.0f,
        (float)winHeight * 0.5f - ((float)texture.height * 0.5f) * 4.0f};
}

void Character::tick(float deltaTime)
{
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
    Rectangle source{
        frame * (float)texture.width / 6.0f, // x position of rectangle frame
        0.0,
        rightLeft * (float)texture.width / 6.0f,
        (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, (float)texture.width / 6.0f * 4.0f, (float)texture.height * 4.0f};
    DrawTexturePro(texture, source, dest, {0.0, 0.0}, 0.0, WHITE);
}

int main()
{

    // Init window
    const int windowDimension[2]{384, 384};
    InitWindow(windowDimension[0], windowDimension[1], "Classy Clash");

    ////// Level map
    Texture2D levelMap{LoadTexture("nature_tileset/OpenWorldMap24x24.png")};
    Vector2 levelMapPos{0.0, 0.0};

    ////// Character
    Character knight;
    knight.setScreenPos(windowDimension[0], windowDimension[1]);


    ////// Target FPS
    SetTargetFPS(60);

    // ------------------------------------------------- Main loop
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw map
        levelMapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(levelMap, levelMapPos, 0.0, 4.0, WHITE);

        // draw character
        knight.tick(dt);


        EndDrawing();
    }
    UnloadTexture(levelMap);
    CloseWindow();
    return 0;
}