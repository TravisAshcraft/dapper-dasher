#include "raylib.h"

int main()
{
    //window dimensions
    const int WindowHeight = 800;
    const int WindowWidth = 800;
    //intitalize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

    //Acceleration due to gravity (Pixels/Second)/Second
    const int Gravity {1000};
    const int JumpVal {-600};
    bool IsInAir;

//Nebula/hazards variables
    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle NebulaRec{0.0, 0.0, Nebula.width/ 8, Nebula.height/8};
    Vector2 NebulaPos{WindowWidth, WindowHeight - NebulaRec.height};
    int NebulaVel{-600}; //Nebula x velocity (pixels per second)

//Scarfy/Player variables
    //Sprite
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");
    Rectangle ScarfyRec{0.0, 0.0, Scarfy.width/6, Scarfy.height};

    Vector2 ScarfyPos{WindowWidth/2-ScarfyRec.width/2, WindowHeight-ScarfyRec.height};
    int Velocity{0};
    //Animation Frame rate
    int Frame{0};
    //amount of time before animation frame update
    const float UpdateTime{1.0/12.0};
    float RunningTime{};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        //Delta Time
        const float DT{GetFrameTime()};
        
        
        
        //Ground check
        if(ScarfyPos.y >= WindowHeight - ScarfyRec.height)
        {
            //Player on the ground
            Velocity = 0;
            IsInAir = false;
        }
        else{
            
            //Apply gravity
             Velocity += Gravity * DT;
        }
        //Check for jumping
        if(IsKeyDown(KEY_SPACE) && !IsInAir)
        {
            Velocity += JumpVal;
            IsInAir = true;
            
        }

        //Update Nebula Pos
        NebulaPos.x += NebulaVel * DT;
      

        //Update scarfy Position
        ScarfyPos.y += Velocity * DT;
        if(!IsInAir)
        {
            //update runningtime
            RunningTime += DT;
            if(RunningTime >= UpdateTime)
            {
                //Resets running time back to zero
                RunningTime = 0;
                //update animation frame
                ScarfyRec.x = Frame * ScarfyRec.width;
                Frame++;
                if(Frame > 5)
                {
                    //resets frame count to zero to return to the 
                    //first animation and repeat the cycle
                    Frame = 0;
                }
            }
        }
        

        //Draw Nebula
        DrawTextureRec(Nebula, NebulaRec, NebulaPos, WHITE);

        //Draw Scarfy
        DrawTextureRec(Scarfy, ScarfyRec, ScarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    CloseWindow();
}

