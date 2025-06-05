#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // Rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        // End drawing
        EndDrawing();
    }

    CloseWindow();
}