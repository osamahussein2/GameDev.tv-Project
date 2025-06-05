#include "raylib.h"

int main()
{
    // Window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // Acceleration due to gravity (pixels/second) second
    const int gravity{1'000};
    
    int velocity{0};

    bool isInAir{false};

    // Jump velocity (pixels/second)
    const int jumpVel{-600};

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0f, 0.0f, nebula.width / 8, nebula.height / 8};
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    // Nebula velocity in pixels per second
    int nebulaVel{-200};

    int nebulaFrame{};
    const float nebulaUpdateTime{1.0 / 12.0};
    float nebulaRunningTime{};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Animation frame
    int frame{};

    // Amount of time before animation frame is updated (frame independent)
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT = GetFrameTime();

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // Rectangle is on the ground
            velocity = 0;

            if (isInAir != false) isInAir = false;
        }

        else
        {
            // Apply gravity
            velocity += gravity * dT;
        }

        if (IsKeyPressed(KEY_SPACE) && isInAir == false)
        {
            velocity += jumpVel;

            isInAir = true;
        }

        // Update nebula position
        nebulaPos.x += nebulaVel * dT;

        // Update scarfy position
        scarfyPos.y += velocity * dT;

        nebulaRunningTime += dT;

        if (nebulaRunningTime >= nebulaUpdateTime)
        {
            nebulaRunningTime = 0.0f;

            // Update nebula's animation frame
            nebulaRec.x = nebulaFrame * nebulaRec.width;
            nebulaFrame++;
            
            if (nebulaFrame > 7) nebulaFrame = 0;
        }

        if (!isInAir)
        {
            runningTime += dT; // Update running time

            if (runningTime >= updateTime)
            {
                runningTime = 0.0f;

                // Update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if (frame > 5) frame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}