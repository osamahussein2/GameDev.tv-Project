#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy Clash!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"),
    LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"),
    LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy* enemies[]{ &goblin, &slime };

    for (Enemy* enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        
        for (auto prop : props)
        {
            // Draw the props
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();

            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);

            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.Tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f || 
        knight.getWorldPos().y < 0.f ||
        knight.getWorldPos().x + windowWidth > map.width * mapScale || 
        knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            { 
                knight.undoMovement();
            }
        }

        for (Enemy* enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        // If left mouse button is pressed and the knight's sword collides with the goblin
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (Enemy* enemy : enemies) 
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}