#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // Acceleration due to gravity (pixels/frame)
    const int gravity{1};

    // Rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    bool isInAir{false};
    const int jumpVel{-22};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (posY >= windowHeight - height)
        {
            // Rectangle is on the ground
            velocity = 0;

            if (isInAir != false) isInAir = false;
        }

        else
        {
            // Apply gravity
            velocity += gravity;
        }

        if (IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;

            isInAir = true;
        }

        // Update position
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        // End drawing
        EndDrawing();
    }

    CloseWindow();
}