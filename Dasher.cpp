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

    AnimData nebulaData{ {0.0f, 0.0f, nebula.width / 8, nebula.height / 8}, 
    {windowDimensions[0], windowDimensions[1] - nebula.height / 8}, 
    0, 
    1.0 / 12.0, 
    0 
    };

    AnimData nebula2Data{ {0.0f, 0.0f, nebula.width / 8, nebula.height / 8}, 
    {windowDimensions[0] + 300, windowDimensions[1] -  nebula.height / 8}, 
    0, 
    1.0 / 16.0, 
    0 
    };

    AnimData nebulae[2]{ nebulaData, nebula2Data };

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

        // Update nebula position
        nebulae[0].pos.x += nebulaVel * dT;
        nebulae[1].pos.x += nebulaVel * dT; // Update the 2nd nebula's position

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        nebulae[0].runningTime += dT;

        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0f;

            // Update nebula's animation frame
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            
            if (nebulae[0].frame > 7) nebulae[0].frame = 0;
        }

        nebulae[1].runningTime += dT;

        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0f;

            // Update nebula's animation frame
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            
            if (nebulae[1].frame > 7) nebulae[1].frame = 0;
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

        // Draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED); // Draw the 2nd nebula

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}