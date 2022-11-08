//#################################################################################################//
//######################################   SPACE INVADER   ########################################//
//#################################################################################################//
//initialising raylib library
#include "raylib.h"

//creating structure for bullets
struct bullets
{
    Rectangle rect; //rectangle.
    Vector2 speed; //vectore that interpolate x and y.
    bool active;  //bollean to establish if the bullest are active or not.
    Color color; //bullet colour.
};

//main funcion
int main(){
    const int windowWidth {500}; //the window width is a constant integer because it does never change.
    const int windowHeight {500}; //the window height is a constant integer because it does never change.
    int num_bullets {50};  //estaglishing array as integers for the number of bullets.

    InitWindow (windowWidth, windowHeight, "Space Invaders"); //Creating window using the e parameters created above.
    
    Texture2D spaceship = LoadTexture ("resources/spaceship.png"); //leading the png texture for the spaceship.

    //creating rectangle for the spaceship
    Rectangle spaceshipRec; 
    Vector2 spaceshipSpeed;
    spaceshipRec.x = windowWidth/2; //setting up the spaceship rectangle position on the x axis.
    spaceshipRec.y = windowHeight; //setting up the spaceship rectangle position on the y axis.
    spaceshipRec.width = spaceship.width; //setting up the spaceship rectangle width.
    spaceshipRec.height = spaceship.height; //setting up the spaceship rectangle height.
    spaceshipSpeed.x = windowWidth/2 - spaceshipRec.width/2; //setting up the speed movement on the x axis.
    spaceshipSpeed.y = windowHeight - spaceshipRec.height; //setting up the speed movemtn on the y axis.

    //creating bullest rectangle using the structure created in the beginning
    bullets bullet [num_bullets];
    //using for loop so that I don't need to initialise all 50 bullets one by one.
    for (int i = 0; i < num_bullets; i++) //i represents a specific bullet i from i to 50, assuming an increased value for each loop iteration.
    {
        //the for loop will repeat each one of the following sptep 50 times
        bullet[i].rect.height = 7;
        bullet[i].rect.width = 7;
        bullet[i].color = GREEN;
        bullet[i].rect.x = (windowWidth/2) + (spaceshipRec.width/2) - (bullet[i].rect.width/2);
        bullet[i].rect.y = (windowHeight - spaceshipRec.height) - (bullet[i].rect.height);
        bullet[i].speed.x = 50;
        bullet[i].speed.y = -10;
        bullet[i].active = false;
    }

    int shootRate {}; //setting up integer variable for the shooting rate. We put it at 0 for the moment.



    SetTargetFPS (60); //setting up the number of frame per second.
    
    //main loop
    while (!WindowShouldClose()) //while the window is open.
    {
        BeginDrawing(); //start drawing.

        DrawTextureRec (spaceship, spaceshipRec, spaceshipSpeed, WHITE); //draw the rectangle for the spaceship.

        //for loop to draw the bullet rectangle for each and every bullet.
        for (int i = 0; i < num_bullets; i++)
        {
            if (bullet[i].active) //if a certaing bullet i between 1 and 50 is active.
            DrawRectangleRec (bullet[i].rect, bullet[i].color);
        }

        //shooting bullets
        if (IsKeyDown (KEY_SPACE)) //if the spacebar is down.
        {
            shootRate += 5; //increase the shooting rate we previosly establish at 0 by 5.
            //creating for loop to make bullets move
            for (int i = 0; i < num_bullets; i++)
            {
                if (!bullet[i].active && shootRate % 40 ==0) //if a certain bullet i is active and the shooting rate reminder of the division by 40 is 0;
                {
                    bullet[i].rect.x = spaceshipSpeed.x;
                    bullet[i].rect.y = spaceshipSpeed.y + spaceshipRec.height/4;
                    bullet[i].active = true;
                    break; //exiting the loop despite we don't know how many iterations are needed in the loop.
                }
            }
        }

        for (int i = 0; i < num_bullets; i++)
        {
            if (bullet[i].active)
            {
                bullet[i].rect.y += bullet[i].speed.y;
                if (bullet[i].rect.y <= 0)
                {
                    bullet[i].active = false;
                    shootRate = 0;
                } 
            }
        }

//moving the spaceship
if (IsKeyDown (KEY_LEFT)) //is the left arrow is down.
{
    spaceshipSpeed.x -= 3; //the spaceship speed should decrease by 3.
}
if (IsKeyDown (KEY_RIGHT)) //if the right key is down.
{
    spaceshipSpeed.x += 3; //the spaceship speed should inclease by 3.
}
if (spaceshipRec.x < 0 || spaceshipRec.x > windowWidth - spaceshipRec.width) {
    spaceshipSpeed.x = 0;
}

        ClearBackground (WHITE); //clear the backgroung.
        EndDrawing(); //finish drawing.
    }
UnloadTexture (spaceship); //unload the spaceship png texture (backend purposes).
CloseWindow(); //close window (backend purposes).
}







