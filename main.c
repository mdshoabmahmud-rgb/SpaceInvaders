#include "raylib.h"
#include "raymath.h"
#define AlienSize 50
#define WindowWidth 1500
#define WindowHeight 900
#define AlienDistance 50
int main(void)
{
    int AlienInX = (WindowWidth/(AlienSize+AlienDistance))-2;
    int AlienInY = (WindowHeight/(2*(AlienSize+AlienDistance)))-1;
    Vector2 AlienPos[AlienInX][AlienInY];
    InitWindow(WindowWidth, WindowHeight, "Space Invaders");
    SetTargetFPS(60);
    AlienPos[0][0] = (Vector2){ 150, 50 };
    Vector2 AlienSpeedX= { 70, 0 };
    for (int AlienPosXDex =0; AlienPosXDex < AlienInX; AlienPosXDex++){
        for(int AlienPosYDex =0; AlienPosYDex < AlienInY; AlienPosYDex++){ 
            AlienPos[AlienPosXDex][AlienPosYDex] = (Vector2){ AlienPos[0][0].x + (AlienSize+AlienDistance)*AlienPosXDex, AlienPos[0][0].y + (AlienSize+AlienDistance)*AlienPosYDex };
        }
    }
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        //Drawing Aliens
        float Time = GetFrameTime();
        for(int AlienPosXDex =0; AlienPosXDex < AlienInX; AlienPosXDex++){
            for(int AlienPosYDex =0; AlienPosYDex < AlienInY; AlienPosYDex++){
                if (AlienPos[AlienInX-1][AlienPosYDex].x + AlienSize >= WindowWidth && AlienSpeedX.x > 0){
                    AlienPos[AlienInX-1][AlienPosYDex].x = WindowWidth - AlienSize;
                    AlienSpeedX.x =AlienSpeedX.x * -1 ;
                    for(int AlienPosXDex =0; AlienPosXDex < AlienInX; AlienPosXDex++){
                        for(int AlienPosYDex =0; AlienPosYDex < AlienInY; AlienPosYDex++){
                    AlienPos[AlienPosXDex][AlienPosYDex].y = AlienPos[AlienPosXDex][AlienPosYDex].y + AlienSize/2;
                }
            }
                }
                else if (AlienPos[0][AlienPosYDex].x <= 0 && AlienSpeedX.x < 0){
                    AlienPos[0][AlienPosYDex].x = 0;
                    AlienSpeedX.x =AlienSpeedX.x * -1 ;
                    for(int AlienPosXDex =0; AlienPosXDex < AlienInX; AlienPosXDex++){
                        for(int AlienPosYDex =0; AlienPosYDex < AlienInY; AlienPosYDex++){
                    AlienPos[AlienPosXDex][AlienPosYDex].y = AlienPos[AlienPosXDex][AlienPosYDex].y + AlienSize/2;
                }
            }
                }
                AlienPos[AlienPosXDex][AlienPosYDex]=Vector2Add(AlienPos[AlienPosXDex][AlienPosYDex], Vector2Scale(AlienSpeedX, Time));
                Rectangle Alien = { AlienPos[AlienPosXDex][AlienPosYDex].x, AlienPos[AlienPosXDex][AlienPosYDex].y, AlienSize, AlienSize };
                DrawRectangleRec(Alien, RED);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
} 
