#include "raylib.h"

int main()
{
    // Window dimensions
    int width = 800;
    int height = 450;
    InitWindow(width, height, "Osama's Window");

    // Circle coordinates
    int circle_x{200};
    int circle_y{200};

    int circle_radius{25};

    // Axe coordinates
    int axe_x{400};
    int axe_y{0};

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game logic begins
        DrawCircle(circle_x, circle_y, circle_radius, BLUE);
        DrawRectangle(axe_x, axe_y, 50, 50, RED);

        // Move the axe
        axe_y += 10;

        // Subtract circle radius to it to make sure the whole circle is visible in the window boundaries
        if (IsKeyDown(KEY_D) && circle_x < 350 - circle_radius)
        {
            circle_x += 10; // Move right
        }

        // Add circle radius to it to make sure the whole circle is visible in the window boundaries
        if (IsKeyDown(KEY_A) && circle_x > circle_radius)
        {
            circle_x -= 10; // Move left
        }

        // Game logic ends
        EndDrawing();
    }
}