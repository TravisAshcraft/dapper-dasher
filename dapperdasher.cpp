#include "raylib.h"

//Structure for animdata takes 5 Params Animdata{Rectangle Rec, Vector2 pos, int Frame, float UpdateTime, float RunningTime}
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

    int WindowDimension[2];
    WindowDimension[0] = 800;
    WindowDimension[1] = 800;
 
    //intitalize window
    InitWindow(WindowDimension[0], WindowDimension[1], "Dapper Dasher");

    //Acceleration due to gravity (Pixels/Second)/Second
    const int Gravity {1000};
    const int JumpVal {-600};
    bool IsInAir;

//Nebula/hazards variables

    //Animdata for Nebula
    

    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData NebData{{0.0, 0.0, Nebula.width/8, Nebula.height/8},//Rectangle info
                     {WindowDimension[0], WindowDimension[1] - Nebula.height/8},//Vector2 info
                     0,//Frame info
                     1.0/12.0,//Update time
                     0//RunningTime info
                    };
   
    
    int NebulaVel{-300}; //Nebula x velocity (pixels per second)

//Scarfy/Player variables
    //Sprite
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");
    AnimData ScarfyData;
    ScarfyData.Rec.width = Scarfy.width/6;
    ScarfyData.Rec.height = Scarfy.height;
    ScarfyData.Rec.x = 0;
    ScarfyData.Rec.y = 0;
    ScarfyData.Pos.x = WindowDimension[0]/2-ScarfyData.Rec.width/2;
    ScarfyData.Pos.y = WindowDimension[1]-ScarfyData.Rec.height;
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
        if(ScarfyData.Pos.y >= WindowDimension[0] - ScarfyData.Rec.height)
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
        NebData.Pos.x += NebulaVel * DT;
      

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
        NebData.RunningTime += DT;
        if(NebData.RunningTime >= NebData.UpdateTime)
        {
            NebData.RunningTime = 0;
            NebData.Rec.x = NebData.Frame * NebData.Rec.width;
            NebData.Frame++;
            if(NebData.Frame > 7)
            {
                NebData.Frame = 0;
            }
        }
        

        //Draw Nebula
        DrawTextureRec(Nebula, NebData.Rec, NebData.Pos, WHITE);

        //Draw Scarfy
        DrawTextureRec(Scarfy, ScarfyData.Rec, ScarfyData.Pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    CloseWindow();
};

