#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window dimensions
    const int windowDimensions[2] = {512, 380};

    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // Acceleration due to gravity (pixels/second) second
    const int gravity{1'000};
    
    int velocity{0};

    bool isInAir{false};

    // Jump velocity (pixels/second)
    const int jumpVel{-600};

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{10};

    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0f;
        nebulae[i].rec.y = 0.0f;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;

        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
        nebulae[i].pos.y = windowDimensions[1] -  nebula.height / 8;

        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
    }

    // Nebula velocity in pixels per second
    int nebulaVel{-200};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;

    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;

    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT = GetFrameTime();

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Update nebula position
            nebulae[i].pos.x += nebulaVel * dT;
        }

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].runningTime += dT;

            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0f;

                // Update nebula's animation frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                
                if (nebulae[i].frame > 7) nebulae[i].frame = 0;
            }
        }

        if (!isInAir)
        {
            scarfyData.runningTime += dT; // Update running time

            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0f;

                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;

                if (scarfyData.frame > 5) scarfyData.frame = 0;
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}