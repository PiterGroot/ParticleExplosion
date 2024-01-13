#include "Cell.h"

#include "raylib.h"
#include <iostream>

int timeScale = 1;
const int cellCount = 100000;

//skipping frames
float skipTimer;
float skipTime = .05f;
bool skipTimerActive = false;

Cell* cells = (Cell*)malloc(cellCount * sizeof(Cell));

constexpr auto WIDTH = 512;
constexpr auto HEIGHT = 512;

int main()
{
    //create cells
    for (long int i = 0; i < cellCount; i++)
    {
        cells[i] = Cell(WIDTH, HEIGHT);
    }
    
    InitWindow(WIDTH, HEIGHT, "Raylib goo brrrrrrrrrrr"); //create raylib window
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        float deltaTime = GetFrameTime(); //calculate deltaTime
        for (int i = 0; i < cellCount; i++)
        {
            if (!cells[i].active) //skip inactive cells
                continue;

            cells[i].Update(deltaTime * timeScale); //update every cell
            cells[i].Draw(); //draw every cell
        }

        if (IsKeyPressed(KEY_SPACE)) //toggle time scale for pause effect
        {
            if (timeScale == 1)
                timeScale = 0;
            else timeScale = 1;
        }

        if (IsKeyPressed(KEY_RIGHT) && !skipTimerActive) //go couple frames forward
        {
            timeScale = 1;
            skipTimer = 0;
            skipTimerActive = true;
        }

        if (IsKeyPressed(KEY_LEFT) && !skipTimerActive) //go couple frames backwards
        {
            timeScale = -1;
            skipTimer = 0;
            skipTimerActive = true;
        }

        skipTimer += deltaTime; //advance skip timer
        if (skipTimer >= skipTime && skipTimerActive) 
        {
            skipTimerActive = false;
            timeScale = 0;
        }
        
        DrawFPS(0, 0); //draw current fps
        EndDrawing();
    }

    CloseWindow();
    return 0;
}