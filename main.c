#include "raylib.h"
#include "raymath.h"
#define WindowWidth 1500
#define WindowHeight 900

#define AlienSize 50
#define AlienDistance 50
#define AlienSpeedX 20
#define AlienSpeedY 0
#define AlienSprite 3
#define AlienSpriteStyle 2

#define HeroWidth 100//156
#define HeroHeight 135 //150
#define HeroSpeedX 500
void DownAlien(int AlienInX, int AlienInY, Vector2 AlienPos[AlienInX][AlienInY]){
    for(int X =0; X < AlienInX; X++){
        for(int Y =0; Y < AlienInY; Y++){
            AlienPos[X][Y].y += AlienSize/2;
        }
    }
}
int main(void)
{
    InitWindow(WindowWidth, WindowHeight, "Space Invaders");
    SetTargetFPS(60);
    //Alien speed and position
    int AlienInX = (WindowWidth/(AlienSize+AlienDistance))-2;
    int AlienInY = (WindowHeight/(2*(AlienSize+AlienDistance)));
    Vector2 AlienPos[AlienInX][AlienInY];
    AlienPos[0][0] = (Vector2){ 150, 50 };
    Vector2 AlienSpeed= { AlienSpeedX, AlienSpeedY };
    for (int X =0; X < AlienInX; X++){
        for(int Y =0; Y < AlienInY; Y++){ 
            AlienPos[X][Y].x = AlienPos[0][0].x + (AlienSize+AlienDistance)*X;
            AlienPos[X][Y].y = AlienPos[0][0].y + (AlienSize+AlienDistance)*Y;
        }
    }
    Texture2D AlienTexture[AlienSprite][AlienSpriteStyle];
    Texture2D HeroTexture = LoadTexture("assets/sprites/Hero.png");
    AlienTexture[0][0] = LoadTexture("assets/sprites/Alien1style1.png");
    AlienTexture[0][1] = LoadTexture("assets/sprites/Alien1style2.png");
    AlienTexture[1][0] = LoadTexture("assets/sprites/Alien2style1.png");
    AlienTexture[1][1] = LoadTexture("assets/sprites/Alien2style2.png");
    AlienTexture[2][0] = LoadTexture("assets/sprites/Alien3style1.png");
    AlienTexture[2][1] = LoadTexture("assets/sprites/Alien3style2.png");
    //Hero position and speed
    Vector2 HeroPos = { WindowWidth/2, WindowHeight-HeroHeight };
    Vector2 HeroSpeed ={0,0};
    //Frame Calculation
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        float Time = GetFrameTime();
//movement of aliens
        if (AlienPos[AlienInX-1][0].x + AlienSize >= WindowWidth && AlienSpeed.x > 0)
        {
            AlienSpeed.x *= -1 ;
            DownAlien(AlienInX, AlienInY, AlienPos);
        }
        else if (AlienPos[0][0].x <= 0 && AlienSpeed.x < 0)
        {
            AlienSpeed.x *= -1 ;
            DownAlien(AlienInX, AlienInY, AlienPos);
        }
//movement of aliens end
//Drawing of aliens 
        for(int X =0; X < AlienInX; X++){
            for(int Y =0; Y < AlienInY; Y++){
                AlienPos[X][Y]=Vector2Add(AlienPos[X][Y], Vector2Scale(AlienSpeed, Time));
                Rectangle Alien = { AlienPos[X][Y].x, AlienPos[X][Y].y, AlienSize, AlienSize };
                int AStyle = (int)(GetTime()/(0.1))%2;
                DrawTexturePro(
                    AlienTexture[Y%AlienSprite][AStyle],
                    (Rectangle){ 0, 0, AlienTexture[Y%AlienSprite][AStyle].width, AlienTexture[Y%AlienSprite][AStyle].height },
                    Alien, (Vector2){ 0, 0 },
                    0.0f,
                    WHITE
                );
                
            }
        }
//Drawing of Hero and movement
        if (IsKeyDown(KEY_RIGHT))
        {
            HeroSpeed.x = HeroSpeedX;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            HeroSpeed.x = -HeroSpeedX;
        }
        else
        {
            HeroSpeed.x = 0;
        }
//Edge detection of Hero
        HeroPos = Vector2Add(HeroPos, Vector2Scale(HeroSpeed, Time));
        if (HeroPos.x <= HeroWidth/2)
        {
            HeroPos.x = HeroWidth/2;
        }
        else if (HeroPos.x + HeroWidth/2 >= WindowWidth)
        {
            HeroPos.x = WindowWidth - HeroWidth/2;
        }
//Drwaing hero
        Rectangle Hero = { HeroPos.x-HeroWidth/2, HeroPos.y, HeroWidth, HeroHeight };
        DrawTexturePro(HeroTexture, (Rectangle){ 0, 0, HeroTexture.width, HeroTexture.height }, Hero, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }
    UnloadTexture(HeroTexture);
    for (int Asprite = 0; Asprite < AlienSprite; Asprite++)
    {
        for (int AStyle = 0; AStyle < AlienSpriteStyle; AStyle++)
        {
            UnloadTexture(AlienTexture[Asprite][AStyle]);
        }
    }
    CloseWindow();
    return 0;
} 
