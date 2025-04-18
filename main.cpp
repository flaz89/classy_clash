#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Character.h"
#include "Prop.h"

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
   
    ////// Props
    Prop props[2] {
        Prop{Vector2{600.f, 300.f}, Texture2D{LoadTexture("nature_tileset/Rock.png")}},
        Prop{Vector2{400.f, 500.f}, Texture2D{LoadTexture("nature_tileset/Log.png")}},
    };


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

        // draw props fom array
        for (Prop prop : props) {
            prop.render(knight.getWorldPos());
        }
       

        // draw character
        knight.tick(dt);
        // check map bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f || 
            knight.getWorldPos().x + windowDimension[0] > levelMap.width * mapScale || 
            knight.getWorldPos().y + windowDimension[1] > levelMap.height * mapScale) 
        {
            knight.undoMovements();
        }

        // check prop collisions
        for (Prop prop : props) {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos()))) {
                knight.undoMovements();
            };
        }
        

        EndDrawing();
    }
    UnloadTexture(levelMap);
    CloseWindow();
    return 0;
}