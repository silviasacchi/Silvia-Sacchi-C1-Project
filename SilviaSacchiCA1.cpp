//#################################################################################################//
//######################################   SPACE INVADER   ########################################//
//#################################################################################################//
//initialising raylib library
#include "raylib.h"

//creating structure for bullets
typedef struct bullets
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
} bullets;

int main(){
    const int windowWidth {500};
    const int windowHeight {500};
    int num_bullets {50};

    InitWindow (windowWidth, windowHeight, "Space Invaders");
    
    Texture2D spaceship = LoadTexture ("resources/spaceship.png");

    Rectangle spaceshipRec;
    Vector2 spaceshipSpeed;
    spaceshipRec.x = windowWidth/2;
    spaceshipRec.y = windowHeight;
    spaceshipRec.width = spaceship.width;
    spaceshipRec.height = spaceship.height;
    spaceshipSpeed.x = windowWidth/2 - spaceshipRec.width/2;
    spaceshipSpeed.y = windowHeight - spaceshipRec.height;

    SetTargetFPS (60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTextureRec (spaceship, spaceshipRec, spaceshipSpeed, WHITE);
        ClearBackground (WHITE);
        EndDrawing();
    }
UnloadTexture (spaceship);
CloseWindow();
}







