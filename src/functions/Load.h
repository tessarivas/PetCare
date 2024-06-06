#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::atoi;
using std::string;

void LlenarCampos();

void LlenarCampos(){
    float timetolive = 2.0f;
    float actualtime = 0.0f;
    
    Texture2D campos = LoadTexture("../assets/VA/PetCareCampos.png");

    actualtime=0.0f;
    while(actualtime <= timetolive){
        actualtime +=GetFrameTime();
        BeginDrawing();
            DrawTexture(campos,0,0,WHITE);
            if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE)){
                break;
            }
        EndDrawing();
    }
    UnloadTexture(campos);
}