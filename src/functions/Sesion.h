#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

#include "../clases/Usuario.h"

using std::cout;
using std::endl;
using std::atoi;
using std::string;

// ---------- Prototipo ---------- //
Usuario IniciarSesion(int screenWidth,int screenHeight);

// ---------- Funciones ---------- //
Usuario IniciarSesion(int screenWidth,int screenHeight){
    
    // ----------- recursos ----------- //
    // Fondo
    Texture2D Background=LoadTexture("../assets/VA/PetCareIniciarSesionVA.png");
    Texture2D RecBackground=LoadTexture("../assets/VA/PetCareIntenteloMasTarde.png");

    // Fuente
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // termino de iniciar sesion?
    bool finish = false;

    // Mouse
    Vector2 Mouse;
    // Click
    Vector2 Click;
    // color transparente
    Color trans ={255,0,0,100};

    // user temporal
    Usuario user;

    // --------- Cuadros de texto --------- //
    const int MaxCharacter = 20;
    
    char name[MaxCharacter +1] = {""};
    int nameCount = 0;

    char pas[MaxCharacter +1]= {""};
    int pasCount = 0;

    // --------- HitBox ---------- //
    Rectangle NombreC;
    {
        NombreC.x=screenWidth * 0.13;
        NombreC.y=screenHeight * 0.30;
        NombreC.width = screenWidth * 0.70;
        NombreC.height= screenHeight *0.06;
    }
    
    Vector2 NombreV;
    NombreV.x=NombreC.x+ 10;
    NombreV.y=NombreC.y+10;

    Rectangle PasC;
    {
        PasC.x=screenWidth * 0.13;
        PasC.y=screenHeight * 0.47;
        PasC.width = screenWidth * 0.70;
        PasC.height= screenHeight *0.06;

    }

    Vector2 PasV;
    PasV.x=PasC.x +10;
    PasV.y=PasC.y +10;

    Rectangle ListoC;
    {
        ListoC.x=screenWidth * 0.20;
        ListoC.y=screenHeight * 0.74;
        ListoC.width = screenWidth * 0.60;
        ListoC.height = screenHeight * 0.09;

    }

    Rectangle RecC;
    {
        RecC.x=screenWidth*0.35;
        RecC.y=screenHeight *0.55;
        RecC.width=screenWidth * 0.29;
        RecC.height = screenHeight *0.07;

    }

    while(finish == false){
        Mouse= GetMousePosition();
        BeginDrawing();
            // Actualizar ultimo click
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click=Mouse;
            }

            // Fondo
            DrawTexture(Background,0,0,WHITE);

            /*  HitBox Debug 
            DrawRectangleRec(NombreC,trans);
            DrawRectangleRec(PasC,trans);
            DrawRectangleRec(ListoC,trans);
            DrawRectangleRec(RecC,trans);
            */

            // Nombre
            DrawTextEx(fuente,name,NombreV,24,1.0,BLACK);

            // ------ texto de nombre ------ //
            if(CheckCollisionPointRec(Click,NombreC)){
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (nameCount < MaxCharacter)) 
                    {
                        name[nameCount] = (char)key; 
                        name[nameCount+1] = '\0'; 
                        nameCount++; 
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (nameCount < 0){
                    } else{
                        nameCount--;   
                        name[nameCount] = '\0'; 
                    }
                }

            }

            // Contraseña
            DrawTextEx(fuente,pas,PasV,24,1.0,BLACK);

            // ------ texto de contraseña ------ //
            if(CheckCollisionPointRec(Click,PasC)){
                int key = GetCharPressed();
                while (key > 0)
                {
                    if ((key >= 32) && (key <= 125) && (pasCount < MaxCharacter)) 
                    {
                        pas[pasCount] = (char)key; 
                        pas[pasCount+1] = '\0'; 
                        pasCount++; 
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (pasCount < 0){
                    } else{
                        pasCount--;   
                        pas[pasCount] = '\0'; 
                    }
                }

            }

            // Si presiona recuperar contraseña
            if(CheckCollisionPointRec(Click,RecC)){
                bool bandrec=false;

                while(bandrec==false){
                    BeginDrawing();
                        ClearBackground(WHITE);

                        DrawTexture(RecBackground,0,0,WHITE);

                        if(IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE))
                        {
                            bandrec=true;
                        }
                    EndDrawing();
                }
                Click={0,0};
            }

            if(CheckCollisionPointRec(Click,ListoC)){
                string tempname = string(name);
                string temppas = string(pas);
                user.Nombre=tempname;
                user.Passwoard=temppas;
                cout<<user.Nombre<<" "<<user.Passwoard<<endl;
                finish = true;
            }

        EndDrawing();
    }
    UnloadTexture(Background);
    UnloadTexture(RecBackground);
    return user;
}

Usuario RegistrarUsuario(int screenWidth, int screenHeight){
    // Bandera de salida
    bool finish = false;
    
    // Usuario tempora;
    Usuario user;

    // color transparente
    Color trans ={255,0,0,100};

    // ---------- Text ---------- //
    const int MaxCharacter=20;
    
    // Nombre de usuario
    char name[MaxCharacter +1]={""};
    int nameCount = 0;
    
    // Contrasena
    char pas[MaxCharacter +1]={""};
    int pasCount = 0;
    
    // Contrasenia confirmacion
    char pascon[MaxCharacter +1]={""};
    int pasconCount = 0;

    // ---------- HitBoxes ---------- //
    // Cuadro de nombre
    Rectangle UserC;
    UserC.x=screenWidth *0.14;
    UserC.y=screenHeight *0.30;
    UserC.width = screenWidth * 0.69;
    UserC.height = screenHeight *0.06;
    
    Rectangle PasC;
    PasC.x=screenWidth *0.14;
    PasC.y=screenHeight *0.43;
    PasC.width = screenWidth * 0.69;
    PasC.height = screenHeight *0.06;

    // ---------- Recursos ---------- //
    Texture2D background = LoadTexture("../assets/VA/PetCareNuevoUsuario1VA.png");

    while (finish == false)
    {
        BeginDrawing();
            // Fondo
            DrawTexture(background,0,0,WHITE);

            // ------- Nombre de usuario ------- //
            DrawRectangleRec(UserC,trans);
            DrawRectangleRec(PasC,trans);

        EndDrawing();
    }
    
}
