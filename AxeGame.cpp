#include "raylib.h"

int main()
{
    int width;
    width = 350;

    InitWindow(width, 200, "Osama's Window");

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(width / 2, 200 / 2, 25, BLUE);
        EndDrawing();
    }
}