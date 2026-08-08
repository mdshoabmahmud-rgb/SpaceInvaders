#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "Space Invaders");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Space Invaders", 300, 200, 30, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}