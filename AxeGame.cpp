#include "raylib.h"

int main()
{
    int width;
    width = 350;

    InitWindow(width, 200, "Osama's Window");

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
}