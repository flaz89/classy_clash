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