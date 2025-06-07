#include "raylib.h"
#include "raymath.h"

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy Clash!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    
    float speed{4.0};
    
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)
    };

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    // 1 is for facing right and -1 is for facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0)
        {
            // Set map to map position minus direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

            // Terniary operator for condition checks (if true : else false)
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

            knight = knight_run;
        }

        else
        {
            knight = knight_idle;
        }

        // Draw tha map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();

        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;

            if (frame > maxFrame) frame = 0;
        }

        Rectangle source{ frame * (float)knight.width / 6.0f, 0.0f, 
            rightLeft * (float)knight.width / 6.0f, (float)knight.height };

        Rectangle dest{ knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height };

        // Draw the character
        DrawTexturePro(knight, source, dest, Vector2Zero(), 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}