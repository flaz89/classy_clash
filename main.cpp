#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
    };

    ////// Enemies
    Enemy goblin{
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy goblin2{
        Vector2{300.f, 200.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f}, 
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[] {&goblin, &goblin2, &slime};


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

        if (!knight.getAlive()) { // if player dies
            DrawText("GAME OVER", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        } else { // if layer is alive
            std::string knightHealth {"Health: "};
            knightHealth.append(std::to_string(knight.getHealth()), 0 ,5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
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

        // draw enemies
        for (Enemy* enemy : enemies) {
            enemy->setTarget(&knight);
            enemy->tick(dt);
        }
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            for (Enemy* enemy : enemies) {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec())) {
                    enemy->setAlive(false);
                }
            }
        } 
        
        

        EndDrawing();
    }
    UnloadTexture(levelMap);
    CloseWindow();
    return 0;
}