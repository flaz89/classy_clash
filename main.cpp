#include "raylib.h"
#include "raymath.h"
#include <iostream>

int main() {

    // Init window
    const int windowDimension[2] {384, 384};
    InitWindow(windowDimension[0], windowDimension[1], "Classy Clash");

    // Level map
    Texture2D levelMap {LoadTexture("nature_tileset/OpenWorldMap24x24.png")};
    Vector2 levelMapPos {0.0, 0.0};
    float speedMov {4.0};

    // Character
    Texture2D knight {LoadTexture("characters/knight_idle_spritesheet.png")};
    Vector2 knightPos {
        windowDimension[0] * 0.5f - (knight.width * 0.5f / 6.0f) * 4.0f, 
        windowDimension[1] * 0.5f - (knight.height * 0.5f) * 4.0f
    };
   

    //Target FPS
    SetTargetFPS(60);

    // ------------------------------------------------- Main loop
    while(!WindowShouldClose()) {
        //const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);


        
        Vector2 direction{};
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y += 1.0;
        // Normalize direction checking if vector length is > 0 and subtracting it to map position
        if (Vector2Length(direction) != 0.0) {
            Vector2 scaldeDirection = Vector2Scale(direction, speedMov);
            levelMapPos = Vector2Subtract(levelMapPos, scaldeDirection);
        }
        
        // draw map
        DrawTextureEx(levelMap, levelMapPos, 0.0, 4.0, WHITE);
        
        // draw knight
        Rectangle source {0.0, 0.0, (float)knight.width / 6.0f, (float)knight.height};
        Rectangle dest {knightPos.x, knightPos.y, (float)knight.width / 6.0f * 4.0f, (float)knight.height * 4.0f};
        DrawTexturePro(knight, source, dest, {0.0, 0.0}, 0.0, WHITE);

     
        EndDrawing();
    }
    UnloadTexture(levelMap);
    CloseWindow();
    return 0;
}