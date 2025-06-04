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

    // Circle edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    // Axe coordinates
    int axe_x{400};
    int axe_y{0};

    int axe_length{50};

    // Axe edges
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + axe_length};

    int direction{10};

    bool collision_with_axe{false};

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (collision_with_axe == true)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }

        else
        {
            // Update edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            // Game logic begins
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
        
            // Move the axe
            axe_y += direction;
        
            if (axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }
        
            // Subtract circle radius to it to make sure the whole circle is visible in the window boundaries
            if (IsKeyDown(KEY_D) && circle_x < width - circle_radius)
            {
                circle_x += 10; // Move right
            }
        
            // Add circle radius to it to make sure the whole circle is visible in the window boundaries
            if (IsKeyDown(KEY_A) && circle_x > circle_radius)
            {
                circle_x -= 10; // Move left
            }

            // If axe collides with any part of the circle, set collision with axe to true to show game over text
            if (b_axe_y >= u_circle_y && u_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x)
            {
                collision_with_axe = true;
            }
        }

        // Game logic ends
        EndDrawing();
    }
}