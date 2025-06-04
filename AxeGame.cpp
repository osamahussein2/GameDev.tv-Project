#include "raylib.h"

int main()
{
    // Window dimensions
    int width = 350;
    int height = 200;
    InitWindow(width, height, "Osama's Window");

    // Circle coordinates
    int circle_x{175};
    int circle_y{100};

    int circle_radius{25};

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game logic begins
        DrawCircle(circle_x, circle_y, circle_radius, BLUE);

        // Subtract circle radius to it to make sure the whole circle is visible in the window boundaries
        if (IsKeyDown(KEY_D) && circle_x < 350 - circle_radius)
        {
            circle_x = circle_x + 10; // Move right
        }

        // Add circle radius to it to make sure the whole circle is visible in the window boundaries
        if (IsKeyDown(KEY_A) && circle_x > circle_radius)
        {
            circle_x = circle_x - 10; // Move left
        }

        // Game logic ends
        EndDrawing();
    }
}