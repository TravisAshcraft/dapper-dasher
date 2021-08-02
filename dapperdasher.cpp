#include "raylib.h"

int main()
{
    //window dimensions
    const int WindowHeight = 800;
    const int WindowWidth = 800;
    //intitalize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher");
    
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
        if(IsKeyDown(KEY_SPACE))
        {
            Velocity += -10;
            PosY += Velocity;
        }


        EndDrawing();
    }
    CloseWindow();
}
