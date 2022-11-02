//#################################################################################################//
//######################################   SPACE INVADER   ########################################//
//#################################################################################################//
//initialising raylib library
#include "raylib.h"

//creating scructure for the spaceship.
struct spaceship {
    Rectangle rec; //rectangle.
    Vector2 speed; //vector that interpolate x and y.
    Color colour;  //colour.
};

//ceating structure for bullets.
struct bullets
{
    Rectangle rec;
    Vector2 speed;
    Color colour;
    bool active; //creating boolean variable to show the active state of the bullets.
};

//maing funcion.
int main () {
    const int windowWidth {500}; //window width is a constant because the paramenter doesn't change thorughout the code.
    const int windowHeight {500}; //window height constant variable.
    int num_bullets {50};         //establishing variable for number of bullets

    //creating window
    InitWindow (windowWidth, windowHeight, "Space Invaders");

    //allowing music.
    InitAudioDevice ();

    //loading spaceship texture
    Texture2D spaceship_tex = LoadTexture ("resources/spaceship.png");

    //creating spaceship (the game player).
    spaceship spaceship;
    spaceship.rec.height = spaceship_tex.height;
    spaceship.rec.width = spaceship_tex.width;   
    spaceship.colour = WHITE;
    spaceship.rec.x = windowWidth/2 - spaceship.rec.width/2;
    spaceship.rec.y = windowHeight - spaceship.rec.height;
    spaceship.speed.x = 10;
    spaceship.speed.y = 0;

    //creating bullets
    bullets bullet [num_bullets];
    for (int i = 0; i < num_bullets; i++)
    {
        bullet[i].rec.height = 10;
        bullet[i].rec.width = 10;
        bullet[i].colour = GREEN;
        bullet[i].rec.x = (windowWidth/2) + (spaceship.rec.width/2) - (bullet[i].rec.height);
        bullet[i].rec.y = (windowHeight - spaceship.rec.height) - (bullet[i].rec.height);
        bullet[i].speed.x = 50;
        bullet[i].speed.y = -10;
        bullet[i].active = false;
    }
    
    //creating shooting rate variable as a integer.
    int shootRate = 0;

    //adding music.

    //set frame per second
    SetTargetFPS (60);

    //while loop
    while (!WindowShouldClose ()) //while the window is open.
    {
        //keep music playing after the music file is finished.
        
        //start draving all the element
        BeginDrawing ();

        //draw spaceship rectangle
        DrawRectangleRec (spaceship.rec, spaceship.colour);
        //for loop
        for (int i = 0; i < num_bullets; i++)
        {
            if (bullet[i].active)
            DrawRectangleRec (bullet[i].rec, bullet[i].colour);
        }

        //making spaceship shoot
        if (IsKeyDown (KEY_SPACE))
        {
            shootRate += 5;
            for (int i = 0; i < num_bullets; i++)
            {
                if (!bullet[i].active && shootRate % 40 == 0)
                {
                    bullet[i].rec.x = spaceship.rec.x;
                    bullet[i].rec.y = spaceship.rec.y + spaceship.rec.height/4;
                    bullet[i].active = true;
                    break; //used to exit a loop when we don't know after how many iterations it will be over.
                }
            }
        }
            for (int i = 0; i < num_bullets; i++)
            {
                if (bullet[i].active)
                {
                    bullet[i].rec.y += bullet[i].speed.y;

                    if (bullet[i].rec.y = 0)
                    {
                        bullet[i].active = false;
                        shootRate = 0;
            }
        }
    }
     //make spaceship move.
    if (IsKeyPressed (KEY_A) && spaceship.rec.x > windowWidth - spaceship.rec.width)
    {
        spaceship.speed.x = -10;
    }
    if (IsKeyPressed (KEY_D) && spaceship.rec.x <0)
    {
        spaceship.speed.x = 0;
    }
    spaceship.rec.x += spaceship.speed.x;
    if (spaceship.rec.x < 0 || spaceship.rec.x > windowWidth - spaceship.rec.width)
    {
        spaceship.speed.x = 0;
    }

    //clear the background
    ClearBackground (WHITE);

    //Ending drawing 
    EndDrawing();
    }
    
    //stopping music
    CloseAudioDevice();

    //unload the spaceship texture for backhand purposes.
    UnloadTexture (spaceship_tex);

    //close the window of the game. It's just for backhand reasons as we close it manually.
    CloseWindow();
}







