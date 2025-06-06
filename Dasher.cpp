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
        nebulaData.pos.x += nebulaVel * dT;
        nebula2Data.pos.x += nebulaVel * dT; // Update the 2nd nebula's position

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        nebulaData.runningTime += dT;

        if (nebulaData.runningTime >= nebulaData.updateTime)
        {
            nebulaData.runningTime = 0.0f;

            // Update nebula's animation frame
            nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
            nebulaData.frame++;
            
            if (nebulaData.frame > 7) nebulaData.frame = 0;
        }

        nebula2Data.runningTime += dT;

        if (nebula2Data.runningTime >= nebula2Data.updateTime)
        {
            nebula2Data.runningTime = 0.0f;

            // Update nebula's animation frame
            nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
            nebula2Data.frame++;
            
            if (nebula2Data.frame > 7) nebula2Data.frame = 0;
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
        DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
        DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED); // Draw the 2nd nebula

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}