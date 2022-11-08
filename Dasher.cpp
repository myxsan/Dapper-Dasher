#include "raylib.h"

int main()
{
    //Window resolutions
    const int windowWidth{512};
    const int windowHeight{380};
    
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    float velocity{0};
    const int jumpVelocity{-7000};

    //Acceleration due to gravity (pixel / frame) / frame
    const int gravity{1'00};

    //Nebula values
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebPos{};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //Animation Frame
    int frame{};
    float runningTime{};
    const float updateTime{1.0 / 12.0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);
        //Game Logic
        
        //Apply gravity
        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            velocity = 0;
            //Get input to jump
            if(IsKeyPressed(KEY_SPACE))
            {
                velocity += jumpVelocity * deltaTime;
            }
        }else
        {
            velocity += gravity * deltaTime;
        }

        //Update position
        scarfyPos.y += velocity * deltaTime;
        
        //Update Animation frame
        runningTime += deltaTime;
        if(runningTime >= updateTime)
        {
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5) frame = 0;
            runningTime = 0;
        }
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}