#include "raylib.h"

int main()
{
    //window dimensions
    const int WindowHeight = 800;
    const int WindowWidth = 800;
    //intitalize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");

    //Acceleration due to gravity (Pixels/Frame)/Frame
    const int Gravity {1};
    const int JumpVal {-22};
    bool IsInAir;

    //Sprite
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");
    Rectangle ScarfyRec;
    Vector2 ScarfyPos;
    
    //rectangle dimensions
    const int width{50};
    const int height{50};

    int PosY{WindowHeight - height};
    int Velocity{0};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        
        DrawRectangle(WindowWidth/2, PosY, width, height, RED);
        
        //Ground check
        if(PosY >= WindowHeight -height)
        {
            //Player on the ground
            Velocity = 0;
            IsInAir = false;
        }
        else{
            //Apply gravity
             Velocity += Gravity;
        }
        //Check for jumping
        if(IsKeyDown(KEY_SPACE) && !IsInAir)
        {
            Velocity += JumpVal;
            IsInAir = true;
            
        }
      

        //Update Position
        PosY += Velocity;

        EndDrawing();
    }
    CloseWindow();
}

