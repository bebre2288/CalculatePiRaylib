#include "raylib.h"
#include "raymath.h"

#define SMAL_M_DEF 10
#define BIG_M_DEF 100000
#define BIG_V_DEF -1

int main(int argc, char *argv[]){
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Load test");
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    InitAudioDevice();
    Sound click = LoadSound("click.wav");

    int text_height = GetScreenHeight()/10;
    int size_unit =  GetScreenHeight()*0.1;
    Rectangle ground =  {0, GetScreenHeight()-size_unit, GetScreenWidth(), size_unit};
    // configuring our booooys
    Rectangle big_boy =  {GetScreenWidth()/2, ground.y-ground.height-size_unit*2, size_unit*3, size_unit*3};
    float big_boy_m = BIG_M_DEF;
    float big_boy_vel = BIG_V_DEF;
    Rectangle smal_boy = {GetScreenWidth()/4, ground.y-ground.height, size_unit*1, size_unit*1};
    float smal_boy_vel = 0;
    float smal_boy_m = SMAL_M_DEF;
    int collisions = 0;
    while (!WindowShouldClose()){
        if(IsKeyPressed(KEY_R)){ // reset
            big_boy.x = GetScreenWidth()/2;
            big_boy.y = ground.y-ground.height-size_unit*2;
            big_boy.width = size_unit*3;
            big_boy.height = size_unit*3;
            big_boy_m = BIG_M_DEF;
            big_boy_vel = BIG_V_DEF;

            smal_boy.x = GetScreenWidth()/4;
            smal_boy.y = ground.y-ground.height;
            smal_boy.width = size_unit*1;
            smal_boy.height = size_unit*1;
            smal_boy_vel = 0;
            smal_boy_m = SMAL_M_DEF;
            collisions = 0;
         
        }
        text_height = GetScreenHeight()/10;
        size_unit =  GetScreenHeight()*0.1;
        // ground prop update
        ground.y = GetScreenHeight()-size_unit;
        ground.width = GetScreenWidth();
        ground.height = size_unit;
        // big_boy props update
        big_boy.y = ground.y-ground.height-size_unit*2;
        big_boy.x+=big_boy_vel;
        // smal_boy props update
        smal_boy.y = ground.y-ground.height;
        smal_boy.x+=smal_boy_vel;

        if(big_boy.x<=smal_boy.x+smal_boy.width){
            PlaySound(click);
            // v1 = ((m1-m2)/(m1+m2))*u1 + (2*m2/(m1+m2))*u2
            // v2 = ((2*m1/(m1+m2))*u1 + (m2-m1)/(m1+m2))*u2
            //big_boy.x=smal_boy.x+smal_boy.width;
            float bbv = big_boy_vel;
            float sbv = smal_boy_vel;
            big_boy_vel = ((big_boy_m-smal_boy_m)/(big_boy_m+smal_boy_m))*bbv+(2*smal_boy_m/(big_boy_m+smal_boy_m))*sbv;
            smal_boy_vel = ((smal_boy_m-big_boy_m)/(big_boy_m+smal_boy_m))*sbv+(2*big_boy_m/(big_boy_m+smal_boy_m))*bbv;
            collisions++;
        }
        if(smal_boy.x<=0){
            PlaySound(click);
            smal_boy_vel = -smal_boy_vel;
            collisions++;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawFPS(10, 10);
            DrawText(TextFormat("big: %.4f", big_boy_vel), 10, 10+text_height, text_height, BLACK);
            DrawText(TextFormat("small: %.4f", smal_boy_vel), 10, 10+text_height*2, text_height, BLACK);
            DrawText(TextFormat("PI: %5d", collisions), 10, 10+text_height*3, text_height, BLACK);
            DrawRectangleRec(ground, DARKGRAY);
            DrawRectangleRec(big_boy, RED);
            DrawRectangleRec(smal_boy, GREEN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
