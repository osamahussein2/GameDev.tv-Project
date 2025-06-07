#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void Tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 screenPos{};
    Vector2 worldPos{};

    // 1 is for facing right and -1 is for facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};

    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {(float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
                 (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::Tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // Set world position to world position plus direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        // Terniary operator for condition checks (if true : else false)
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }

    else
    {
        texture = idle;
    }

    // Update animation frame
    runningTime += deltaTime;
    
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        
        if (frame > maxFrame) frame = 0;
    }
    
    Rectangle source{frame * (float)texture.width / 6.0f, 0.0f,
        rightLeft * (float)texture.width / 6.0f, (float)texture.height};
        
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};

    // Draw the character
    DrawTexturePro(texture, source, dest, Vector2Zero(), 0.0f, WHITE);
}

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy Clash!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw tha map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.Tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}