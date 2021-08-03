#include "raylib.h"

struct AnimData
{
    Rectangle Rec;
    Vector2 Pos;
    int Frame;
    float UpdateTime;
    float RunningTime;
};

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
    int NebulaVel{-300}; //Nebula x velocity (pixels per second)

    int NebFrame{0};
    const float NebUpdateTime{1.0/12.0};
    float NebRunningTime{};

//Scarfy/Player variables
    //Sprite
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");
    AnimData ScarfyData;
    ScarfyData.Rec.width = Scarfy.width/6;
    ScarfyData.Rec.height = Scarfy.height;
    ScarfyData.Rec.x = 0;
    ScarfyData.Rec.y = 0;
    ScarfyData.Pos.x = WindowWidth/2-ScarfyData.Rec.width/2;
    ScarfyData.Pos.y = WindowHeight-ScarfyData.Rec.height;
    ScarfyData.Frame = 0;
    ScarfyData.UpdateTime = 1.0/12.0;
    ScarfyData.RunningTime = 0;
    


    int Velocity{0};


    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        //Delta Time
        const float DT{GetFrameTime()};
        
        
        
        //Ground check
        if(ScarfyData.Pos.y >= WindowHeight - ScarfyData.Rec.height)
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
        ScarfyData.Pos.y += Velocity * DT;
        if(!IsInAir)
        {

           
            //update scarfy's animation frame
            ScarfyData.RunningTime += DT;
            if(ScarfyData.RunningTime >= ScarfyData.UpdateTime)
            {
                //Resets running time back to zero
                ScarfyData.RunningTime = 0;
                //update animation frame
                ScarfyData.Rec.x = ScarfyData.Frame * ScarfyData.Rec.width;
                ScarfyData.Frame++;
                if(ScarfyData.Frame > 5)
                {
                    //resets frame count to zero to return to the 
                    //first animation and repeat the cycle
                    ScarfyData.Frame = 0;
                }
            }
        }

        //Updat nebula animation frame
        NebRunningTime += DT;
        if(NebRunningTime >= NebUpdateTime)
        {
            NebRunningTime = 0;
            NebulaRec.x = NebFrame * NebulaRec.width;
            NebFrame++;
            if(NebFrame > 7)
            {
                NebFrame = 0;
            }
        }
        

        //Draw Nebula
        DrawTextureRec(Nebula, NebulaRec, NebulaPos, WHITE);

        //Draw Scarfy
        DrawTextureRec(Scarfy, ScarfyData.Rec, ScarfyData.Pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    CloseWindow();
};

