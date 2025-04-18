#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Character.h"

int main()
{

    // Init window
    const int windowDimension[2]{384, 384};
    InitWindow(windowDimension[0], windowDimension[1], "Classy Clash");

    ////// Level map
    Texture2D levelMap{LoadTexture("nature_tileset/OpenWorldMap24x24.png")};
    Vector2 levelMapPos{0.0, 0.0};
    const float mapScale{4.0};

    ////// Character
    Character knight{windowDimension[0], windowDimension[1]};


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
        DrawTextureEx(levelMap, levelMapPos, 0.0, mapScale, WHITE);

        // draw character
        knight.tick(dt);
        // check map bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f || 
            knight.getWorldPos().x + windowDimension[0] > levelMap.width * mapScale || 
            knight.getWorldPos().y + windowDimension[1] > levelMap.height * mapScale) {
                knight.undoMovements();
            }

        EndDrawing();
    }
    UnloadTexture(levelMap);
    CloseWindow();
    return 0;
}