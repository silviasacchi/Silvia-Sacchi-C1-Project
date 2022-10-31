//#################################################################################################//
//######################################   SPACE INVADER   ########################################//
//#################################################################################################//
//initialising raylib library
#include "raylib.h"

//creating scructure for the spaceship
struct spaceship
{
    Rectangle rec;     //rectangle
    Vector2 pos;       //vector that connect x and y.
    int frame;         //frame will take integer values.
    float updateTime;  //updateTime will take floating values.
    float runningTime; //runningTime will take floating values.
};










