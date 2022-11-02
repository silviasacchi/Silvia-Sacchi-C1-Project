//#################################################################################################//
//######################################   SPACE INVADER   ########################################//
//#################################################################################################//
//initialising raylib library
#include "raylib.h"

//creating scructure for the spaceship
struct Anim
{
    Rectangle rec;     //rectangle
    Vector2 pos;       //vector that connect x and y.
    int frame;         //frame will take integer values.
    float updateTime;  //update time will take float values.
    float runningTime; //running time will take float values.
};

//main function
int main () {

//creating all needed variables
const int windowWidth {750};      //the window width won't change during the code so we use a constant.
const int windowHeight {1000};    //the window height won't change during the code so we use a constant. 
int speed {150};                  //establishing variable for spaceship speed as integer.
int frame {};                     //creating variable frame as integer and setting it up to 0.
const float updateTime {1.0/12};  //creating constant float variable for update time.
float runningTime {};             //creating float for running time.

//drawing window
InitWindow (windowWidth, windowHeight, "Space Invader");

//loading spaceship texture
Texture2D spaceship = LoadTexture ("resources/spaceship.png");

//calling spaceshipAnim
Anim spaceshipAnim;
spaceshipAnim.rec.width = spaceship.width;
spaceshipAnim.rec.height = spaceship.height;
spaceshipAnim.rec.x = 0;
spaceshipAnim.rec.y = 0;
spaceshipAnim.pos.x = windowWidth/2 - spaceshipAnim.rec.width/2;
spaceshipAnim.pos.y = windowHeight - spaceshipAnim.rec.height;
spaceshipAnim.frame = 0;
spaceshipAnim.updateTime = 1.0/12.0;
spaceshipAnim.runningTime = 0.0;

//setting up frame for second.
SetTargetFPS(60);
   //while loop
   while (!WindowShouldClose())             //while window is open.
   {
    const float deltaTime {GetFrameTime()}; //create constant float delta time and constantly updates.

    //start drawing
    BeginDrawing ();

    //draw reactangle for spaceship
    DrawTextureRec (spaceship, spaceshipAnim.rec, spaceshipAnim.pos, WHITE);

    //moving spaceship
    //move left
    //if A is down and the position of the spaceship on the x axis is greater than the window width minus the spaceship width.
    if (IsKeyDown (KEY_A) && spaceshipAnim.rec.x > windowWidth - spaceshipAnim.rec.width)       
    {
        spaceshipAnim.speed.x = -10;                
    }
   }
}








