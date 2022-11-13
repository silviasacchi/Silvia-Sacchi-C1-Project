//#################################################################################################//
//######################################   SPACE INVADER (KINDA)  ########################################//
//#################################################################################################//
//initialising raylib library.
#include "raylib.h"

//creating structure for bullets.
struct bullets
{
    Rectangle rect; //rectangle.
    Vector2 speed; //vector that interpolates x and y.
    bool active;  //boollean to establish if the bullets are active or not.
    Color color; //bullet colour.
};

//creating structure for enemies.
struct enemies
{
    Rectangle rect; //rectangle.
    Vector2 speed; //vector that interpolates x and y. 
    bool active; //boolean that indicates if the enemy is active or not.
    Color color; //enemies' colour.
};

//main funcion
int main(){
    const int windowWidth {500}; //the window width is a constant integer because it does never change.
    const int windowHeight {500}; //the window height is a constant integer because it does never change.
    int num_bullets {50}; //estaglishing array as integers for the number of bullets.
    int shootRate {}; //setting up integer variable for the shooting rate. We put it at 0 for the moment.
    int num_enemies {30}; //esablishing array as integers for the number of enemies.
    int activeEnemies {}; //setting up integer variable for the number of enemies active at a certain point in time.
    const char backgroundText [] = "Space Invaders (kinda)"; //creating the text to show in the background of the window game. 

    InitWindow (windowWidth, windowHeight, "Space Invaders"); //Creating window using the width and height variables created above.
    InitAudioDevice (); //Initialising the audio to allow music and sounds to play.

    Texture2D spaceship = LoadTexture ("resources/spaceship.png"); //loading the png texture for the spaceship.

    //Adding music and sound effects
    Music music = LoadMusicStream ("resources/music.wav"); //loading the background music.
    Sound ShootingSound = LoadSound ("resources/shooting.wav"); //loading shooting sound.
    Sound collision = LoadSound ("resources/collision.wav"); //loading collision sound.
    PlayMusicStream (music); //allolwing background music to play.

    //creating rectangle for the spaceship
    Rectangle spaceshipRec; //ceating the spaceship rectangle.
    Vector2 spaceshipPos; //creating the spaceship position vector.
    spaceshipRec.x = windowWidth/2; //x coordinate of the texture in the rectangle.
    spaceshipRec.y = windowHeight; //y coordinate of the texture in the rectangle.
    spaceshipRec.width = spaceship.width; //spaceship rectangle width.
    spaceshipRec.height = spaceship.height; //spaceship rectangle height.
    spaceshipPos.x = windowWidth/2 - spaceshipRec.width/2; //position of the spaceship within the window on the x axis.
    spaceshipPos.y = windowHeight - spaceshipRec.height; //position of the spaceship within the window on the y axis.

    //creating bullet rectangle using the bullets structure
    bullets bullet [num_bullets];
    //using for loop so that I don't need to initialise all 50 bullets one by one.
    for (int i = 0; i < num_bullets; i++) //i represents a specific bullet i from i to 50, assuming an increased value (+1) for each loop iteration.
    {
        //for loop will repeat each one of the following steps 50 times
        bullet[i].rect.height = 10; //establishing the height of the rectangle of the bullet.
        bullet[i].rect.width = 8; //establishing the width of the rectangle of the bullet.
        bullet[i].color = GREEN; //establishing the colour of the bullet.
        bullet[i].rect.x = (windowWidth/2) + (spaceshipRec.width/2) - (bullet[i].rect.width/2); //etablishing the position of on x axis.
        bullet[i].rect.y = (windowHeight - spaceshipRec.height) - (bullet[i].rect.height); //establishing the position on the y axis.
        bullet[i].speed.x = 50; //establishing movement on the x axis.
        bullet[i].speed.y = -10; //establishing movement on the y axis.
        bullet[i].active = false; //establishing the status of the bullet (active or not).
    }

    //creating enemy rectangle using the enemies structure.
    enemies enemy [num_enemies];
    //setting up the number of active enemies.
    activeEnemies = 4;
    //using for loop so that I don't have to initialised all 30 enemies one by one.
    for (int i = 0; i < num_enemies; i++)
    {
        enemy[i].rect.width = 20;
        enemy[i].rect.height = 20;
        enemy[i].rect.x = GetRandomValue (0, windowWidth); //enemy position on the x axis to be a random number between 0 and the winwow width.
        enemy[i].rect.y = GetRandomValue (-windowHeight, -20); //enemy position on the y axis to be a random number between the window height and 20.
        enemy[i].speed.x = 2;
        enemy[i].speed.y = 2;
        enemy[i].active = true;
        enemy[i].color = BLUE;
    }

    SetTargetFPS (60); //setting up the number of frames per second.
    
    //main loop
    while (!WindowShouldClose()) //while the window is open.
    {
        DrawText (backgroundText, 20, 50, 40, RED); //draw text using the character variable created in the beginning, and then adding the position on the x axis, the one on the y, the font size and the colour.
        UpdateMusicStream (music); //keep playing music in loop. Once it gets to the end of the file it starts back from the beginning.
        
        //for loop to draw the enemy rectangle for each and every enemy. 
        for (int i = 0; i < activeEnemies; i++) //enstablishing i as integer equal to 0, then saying that while i is lower than the max number of enemies the loop will run, and if it runs next time the value of i will increase by 1.
        {
            if (enemy[i].active) //if a certain enemy is active.
            DrawRectangleRec (enemy[i].rect, enemy[i].color); //draw the enemy rectangle.
        }

        //for loop to draw the bullet rectangle for each and every bullet.
        for (int i = 0; i < num_bullets; i++) //enstablishing i as integer equal to 0, then saying that while i is lower than the max number of bullets the loop will run, and if it runs next time the value of i will increase by 1.
        {
            if (bullet[i].active) //if a certain bullet is active.
            {
                DrawRectangleRec (bullet[i].rect, bullet[i].color); //draw the bullet rectangle.

                //check collision between bullets and emenies
                for (int j = 0; j < activeEnemies; j++)
                {
                    if (enemy[j].active) //if the enemy is active
                    {
                        if (CheckCollisionRecs (bullet[i].rect, enemy[j].rect)) //if there is a collision between the rectangle of a certain bullet and the one of a certain enemy.
                        {
                            PlaySound (collision); //play the cound for the collision.
                            bullet[i].active = false; //the bullet is deacivated.
                            enemy[j].rect.x = GetRandomValue (windowWidth, windowHeight + 1000); //the enemy rectangle x positon is a random value between the window width and the window width + 1000.
                            enemy[j].rect.y = GetRandomValue (0, windowHeight - enemy[j].rect.height); //the enemy rectangle y position is a random value between 0 and he window height - he height of the enemy rectangle.
                            shootRate = 0; //the shoot rate is 0.
                        }
                    }
                }
            }
            
        }

        //for loop to make the enemies move
        for (int i = 0; i < activeEnemies; i++)
        {
            if (enemy[i].active) //if the enemy is active.
            {
                enemy[i].rect.y += enemy[i].speed.y; //new position of enemy on the y axis is its old position plus its speed on the y axis.
                //reset if the enemy crosses the boundary
                if (enemy[i].rect.y > windowHeight) //if the enemy goes beyond the bottom of the window.
                {
                    enemy[i].rect.x = GetRandomValue (20, windowWidth - 40); //new enemy position on the x axis.
                    enemy[i].rect.y = GetRandomValue (-windowHeight, -20); //new enemy position on the y axis.
                }
            }
        }

        //shooting bullets
        if (IsKeyDown (KEY_SPACE)) //if the spacebar is down.
        {
            shootRate += 5; //increase the shooting rate we previosly establish at 0 by 5.
            
            //creating for loop to make bullets move
            for (int i = 0; i < num_bullets; i++)
            {
                if (!bullet[i].active && shootRate % 40 ==0) //if a certain bullet i is active and the shooting rate remainder of the division by 40 is 0;
                {
                    PlaySound (ShootingSound); //play the shooting sound.
                    bullet[i].rect.x = spaceshipPos.x;
                    bullet[i].rect.y = spaceshipPos.y + spaceshipRec.height/4;
                    bullet[i].active = true; //the bullet is active.
                    break; //exiting the loop despite the fact that we don't know how many iterations are needed.
                }
            }
        }

        for (int i = 0; i < num_bullets; i++)
        {
            if (bullet[i].active)
            {
                bullet[i].rect.y += bullet[i].speed.y; //the bullet position on the y axis is now equal to its previous position plus its speed.
                if (bullet[i].rect.y <= 0) //if the bullet position on the y axis is below or equal 0.
                {
                    bullet[i].active = false;
                    shootRate = 0;
                } 
            }
        }

//moving the spaceship
if (IsKeyDown (KEY_LEFT)) //is the left arrow is down.
{
    spaceshipPos.x -= 3; //the spaceship should move to the left by 3 units.
}
if (IsKeyDown (KEY_RIGHT)) //if the right key is down.
{
    spaceshipPos.x += 3; //the spaceship speed should move to the right by 3.
}

//making sure the spaceship cannot go outside of the window.
if (spaceshipPos.x <= 0) //if the spaceship touches or goes below the window border on the left.
{
    spaceshipPos.x = 0; //the spaceship position on the x axis is 0.
}
if (spaceshipPos.x >= windowWidth - spaceshipRec.width) //if the spaceship touches or goes below the window border on the right.
{
    spaceshipPos.x = windowWidth - spaceshipRec.width; //the spaceship position on the x axis is the right window border.
}

        BeginDrawing(); //start drawing.
        DrawTextureRec (spaceship, spaceshipRec, spaceshipPos, WHITE); //draw the rectangle for the spaceship.
        ClearBackground (WHITE); //clear the backgroung.
        EndDrawing(); //finish drawing.
    }
UnloadTexture (spaceship); //unload the spaceship png texture (backend purposes).
UnloadMusicStream (music); //unload the background music.
UnloadSound (ShootingSound); //unload the shooting sound.
UnloadSound (collision); //unload the collision sound.
CloseAudioDevice(); //deactivating audio devices.
CloseWindow(); //close window (backend purposes).
}







