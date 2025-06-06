// #include "raylib.h"

// struct AnimData
// {
//     Rectangle rec;
//     Vector2 pos;
//     int frame;
//     float updateTime;
//     float runningTime;
// };

// bool isOnGround(AnimData data, int windowHeight)
// {
//     return data.pos.y >= windowHeight - data.rec.height;
// }

// AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
// {
//     // Update running time
//     data.runningTime += deltaTime;

//     if (data.runningTime >= data.updateTime)
//     {
//         data.runningTime = 0.0;

//         // Update animation frame
//         data.rec.x = data.frame * data.rec.width;
//         data.frame++;

//         if (data.frame > maxFrame) data.frame = 0;
//     }

//     return data;
// }

// int main()
// {
//     // Window dimensions
//     const int windowDimensions[2] = {512, 380};

//     InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

//     // Acceleration due to gravity (pixels/second) second
//     const int gravity{1'000};
    
//     int velocity{0};

//     bool isInAir{false};

//     // Jump velocity (pixels/second)
//     const int jumpVel{-600};

//     // Nebula variables
//     Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

//     const int sizeOfNebulae{10};

//     AnimData nebulae[sizeOfNebulae]{};

//     for (int i = 0; i < sizeOfNebulae; i++)
//     {
//         nebulae[i].rec.x = 0.0f;
//         nebulae[i].rec.y = 0.0f;
//         nebulae[i].rec.width = nebula.width / 8;
//         nebulae[i].rec.height = nebula.height / 8;

//         nebulae[i].pos.x = windowDimensions[0] + (i * 300);
//         nebulae[i].pos.y = windowDimensions[1] -  nebula.height / 8;

//         nebulae[i].frame = 0;
//         nebulae[i].runningTime = 0.0;
//         nebulae[i].updateTime = 1.0 / 16.0;
//     }

//     float finishLine{ nebulae[sizeOfNebulae - 1].pos.x + 100 };

//     // Nebula velocity in pixels per second
//     int nebulaVel{-200};

//     // Scarfy variables
//     Texture2D scarfy = LoadTexture("textures/scarfy.png");

//     AnimData scarfyData;
//     scarfyData.rec.width = scarfy.width / 6;
//     scarfyData.rec.height = scarfy.height;
//     scarfyData.rec.x = 0;
//     scarfyData.rec.y = 0;

//     scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
//     scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;

//     scarfyData.frame = 0;
//     scarfyData.updateTime = 1.0 / 12.0;
//     scarfyData.runningTime = 0.0;

//     Texture2D background = LoadTexture("textures/far-buildings.png");
//     float bgX{};

//     Texture2D midground = LoadTexture("textures/back-buildings.png");
//     float mgX{};

//     Texture2D foreground = LoadTexture("textures/foreground.png");
//     float fgX{};

//     bool collision{false};

//     SetTargetFPS(60);
//     while (!WindowShouldClose())
//     {
//         // Delta time (time since last frame)
//         const float dT = GetFrameTime();

//         // Start drawing
//         BeginDrawing();
//         ClearBackground(WHITE);

//         bgX -= 20 * dT; // Update background
//         if (bgX <= -background.width * 2) bgX = 0.0;

//         mgX -= 40 * dT; // Update midground
//         if (mgX <= -midground.width * 2) mgX = 0.0;

//         fgX -= 80 * dT; // Update foreground
//         if (fgX <= -foreground.width * 2) fgX = 0.0;

//         // Draw background
//         Vector2 bg1Pos{bgX, 0.0};
//         DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        

//         Vector2 bg2Pos{bgX + background.width * 2, 0.0};
//         DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

//         // Draw midground
//         Vector2 mg1Pos{mgX, 0.0};
//         DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        
//         Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
//         DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

//         // Draw foreground
//         Vector2 fg1Pos{fgX, 0.0};
//         DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        
//         Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
//         DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

//         if (isOnGround(scarfyData, windowDimensions[1]))
//         {
//             // Rectangle is on the ground
//             velocity = 0;

//             if (isInAir != false) isInAir = false;
//         }

//         else
//         {
//             // Apply gravity
//             velocity += gravity * dT;
//         }

//         if (IsKeyPressed(KEY_SPACE) && isInAir == false)
//         {
//             velocity += jumpVel;

//             isInAir = true;
//         }

//         for (int i = 0; i < sizeOfNebulae; i++)
//         {
//             // Update nebula position
//             nebulae[i].pos.x += nebulaVel * dT;
//         }

//         // Update finish line
//         finishLine += nebulaVel * dT;

//         // Update scarfy position
//         scarfyData.pos.y += velocity * dT;

//         for (int i = 0; i < sizeOfNebulae; i++)
//         {
//             nebulae[i] = updateAnimData(nebulae[i], dT, 7);
//         }

//         if (!isInAir)
//         {
//             scarfyData = updateAnimData(scarfyData, dT, 5);
//         }

//         for (AnimData nebula : nebulae)
//         {
//             float pad{50};
//             Rectangle nebRec{ 
//                 nebula.pos.x + pad, 
//                 nebula.pos.y + pad, 
//                 nebula.rec.width - 2 * pad, 
//                 nebula.rec.height - 2 * pad 
//             };

//             Rectangle scarfyRec {
//                 scarfyData.pos.x, 
//                 scarfyData.pos.y, 
//                 scarfyData.rec.width, 
//                 scarfyData.rec.height
//             };

//             if (CheckCollisionRecs(nebRec, scarfyRec))
//             {
//                 collision = true;
//             }
//         }

//         if (collision)
//         {
//             // Lose the game
//             DrawText("Game Over!", windowDimensions[0] / 2.5, windowDimensions[1] / 2.5, 20, WHITE);
//         }

//         else 
//         {
//             if (scarfyData.pos.x < finishLine)
//             {
//                 for (int i = 0; i < sizeOfNebulae; i++)
//                 {
//                     // Draw nebula
//                     DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
//                 }

//                 // Draw scarfy
//                 DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
//             }

//             else
//             {
//                 // Win the game
//                 DrawText("You Win!", windowDimensions[0] / 2.5, windowDimensions[1] / 2.5, 20, WHITE);
//             }
//         }

//         // End drawing
//         EndDrawing();
//     }

//     UnloadTexture(scarfy);
//     UnloadTexture(nebula);

//     UnloadTexture(background);
//     UnloadTexture(midground);
//     UnloadTexture(foreground);

//     CloseWindow();
// }