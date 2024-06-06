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
Usuario RegistrarUsuario(int screenWidth, int screenHeight);

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

    Color selected = {204,246,255,255};

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
    
    // Usuario tempora;
    Usuario user;

    // ---------- HitBoxes ---------- //
    // Cuadro de nombre
    Rectangle UserC;
    {
        UserC.x=screenWidth *0.14;
        UserC.y=screenHeight *0.30;
        UserC.width = screenWidth * 0.69;
        UserC.height = screenHeight *0.06;
    }
    
    // Cuadro de contraseña
    Rectangle PasC;
    {
        PasC.x=screenWidth *0.14;
        PasC.y=screenHeight *0.43;
        PasC.width = screenWidth * 0.69;
        PasC.height = screenHeight *0.06;
    }
    
    // Cuadro de confirmacion de contraseña
    Rectangle Pas2C;
    {
        Pas2C.x=screenWidth *0.14;
        Pas2C.y=screenHeight *0.56;
        Pas2C.width = screenWidth * 0.69;
        Pas2C.height = screenHeight *0.06;
    }
    
    // Boton siguiente
    Rectangle ready;
    {
        ready.x=screenWidth *0.20;
        ready.y=screenHeight *0.80;
        ready.width = screenWidth * 0.59;
        ready.height = screenHeight *0.07;
    }

    // ---------- Text ---------- //
    const int MaxCharacter=20;
    
    // Nombre de usuario
    char name[MaxCharacter +1]={""};
    int nameCount = 0;
    
    Vector2 nameV;
    nameV.x=UserC.x+10;
    nameV.y=UserC.y+10;
    
    // Contrasena
    char pas[MaxCharacter +1]={""};
    int pasCount = 0;

    Vector2 pasV;
    pasV.x=PasC.x+10;
    pasV.y=PasC.y+10;
    
    // Contrasenia confirmacion
    char pascon[MaxCharacter +1]={""};
    int pasconCount = 0;

    Vector2 pas2V;
    pas2V.x=Pas2C.x+10;
    pas2V.y=Pas2C.y+10;

    // ----- Extra ----- //
    
    // Mouse
    Vector2 Mouse;
    
    // Ultimo click
    Vector2 Click;

    // Bandera de salida
    bool finish1 = false;
    bool finish2 = false;
    bool finish3 = false;

    // ---------- Recursos ---------- //
    Texture2D background = LoadTexture("../assets/VA/PetCareNuevoUsuario1VA.png");

    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // Color transparente
    Color trans ={255,0,0,100};


    Color selected = {204,246,255,255};

    while (finish1 == false)
    {
        Mouse = GetMousePosition();
        BeginDrawing();
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click=Mouse;
            }
            
            // Fondo
            DrawTexture(background,0,0,WHITE);

            // ------- Nombre de usuario ------- //
            DrawTextEx(fuente,name,nameV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,UserC))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (nameCount <MaxCharacter))
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
            
            // ------- Contrasenia ------- //
            DrawTextEx(fuente,pas,pasV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,PasC))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (pasCount <MaxCharacter))
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
            
            // ------- Confirmar Contrasenia ------- //
            DrawTextEx(fuente,pascon,pas2V,24,1,BLACK);

            if(CheckCollisionPointRec(Click,Pas2C))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (pasconCount <MaxCharacter))
                    {
                        pascon[pasconCount] = (char)key;
                        pascon[pasconCount+1] = '\0'; 
                        pasconCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (pasconCount < 0){
                    } else{
                        pasconCount--;   
                        pascon[pasconCount] = '\0'; 
                    }
                }
            }

            if(CheckCollisionPointRec(Click,ready)){
                finish1=true;
                ClearBackground(WHITE);
                Click={0,0};
            }

        EndDrawing();
    }
    UnloadTexture(background);

    // ------------------------------------ Segunda pantalla ------------------------------------------ //

    // ------------- HitBoxes ------------- //
     Rectangle CorreoC;
    {
        CorreoC.x=screenWidth *0.14;
        CorreoC.y=screenHeight *0.30;
        CorreoC.width = screenWidth * 0.69;
        CorreoC.height = screenHeight *0.06;
    }
    
    // Cuadro de contraseña
    Rectangle CorreoConC;
    {
        CorreoConC.x=screenWidth *0.14;
        CorreoConC.y=screenHeight *0.43;
        CorreoConC.width = screenWidth * 0.69;
        CorreoConC.height = screenHeight *0.06;
    }
    
    // Cuadro de confirmacion de contraseña
    Rectangle NumC;
    {
        NumC.x=screenWidth *0.14;
        NumC.y=screenHeight *0.56;
        NumC.width = screenWidth * 0.69;
        NumC.height = screenHeight *0.06;
    }

    
    // ------------ Recursos -------------- //
    background = LoadTexture("../assets/VA/PetCareNuevoUsuario2VA.png");
    
    // ------- texto --------- //
    // Correo electronico
    const int MaxMailCharacter = 30;
    char correo[MaxMailCharacter +1]={""};
    int correoCount=0;
    
    Vector2 correoV;
    correoV.x=CorreoC.x+10;
    correoV.y=CorreoC.y+10;

    // Confirmacion de correo electronico
    char correoConfirm[MaxCharacter+1]={""};
    int correoConfirmCount=0;

    Vector2 correoConfirmV;
    correoConfirmV.x=CorreoConC.x+10;
    correoConfirmV.y=CorreoConC.y+10;
    
    // Numero de celular
    char numero[MaxCharacter +1]={""};
    int numerCount=0;

    Vector2 numV;
    numV.x=NumC.x+10;
    numV.y=NumC.y+10;

    while (finish2 == false)
    {
        Mouse = GetMousePosition();
        BeginDrawing();
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click=Mouse;
            }
            
            // Fondo
            DrawTexture(background,0,0,WHITE);

            // ------- Correo del usuario ------- //
            DrawTextEx(fuente,correo,correoV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,CorreoC))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (correoCount <MaxMailCharacter))
                    {
                        correo[correoCount] = (char)key;
                        correo[correoCount+1] = '\0'; 
                        correoCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (correoCount < 0){
                    } else{
                        correoCount--;   
                        correo[correoCount] = '\0'; 
                    }
                }
            }
            
            // ------- Confirmacion de correo ------- //
            DrawTextEx(fuente,correoConfirm,correoConfirmV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,CorreoConC))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (correoConfirmCount <MaxMailCharacter))
                    {
                        correoConfirm[correoConfirmCount] = (char)key;
                        correoConfirm[correoConfirmCount+1] = '\0'; 
                        correoConfirmCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (correoConfirmCount < 0){
                    } else{
                        correoConfirmCount--;   
                        correoConfirm[correoConfirmCount] = '\0'; 
                    }
                }
            }
            
            // ------- Numero de celular ------- //
            DrawTextEx(fuente,numero,numV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,NumC))
            {
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (numerCount <MaxCharacter))
                    {
                        numero[numerCount] = (char)key;
                        numero[numerCount+1] = '\0'; 
                        numerCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (numerCount < 0){
                    } else{
                        numerCount--;   
                        numero[numerCount] = '\0'; 
                    }
                }
            }

            if(CheckCollisionPointRec(Click,ready)){
                finish2=true;
                Click = {0,0};
                ClearBackground(WHITE);
            }

        EndDrawing();
    }
    
    UnloadTexture(background);

    // ------------------------------------ Tercera pantalla ------------------------------------------ //

    background = LoadTexture("../assets/VA/PetCareNuevoUsuario3VA.png");

    // ----- Fecha de nacimiento ---- //

    Rectangle DiaC;
    {
        DiaC.x=screenWidth *0.14;
        DiaC.y=screenHeight *0.27;
        DiaC.width = screenWidth *0.21;
        DiaC.height=screenHeight *0.07;
    }

    Rectangle MesC;
    {
        MesC.x=screenWidth *0.37;
        MesC.y=screenHeight *0.27;
        MesC.width = screenWidth *0.23;
        MesC.height=screenHeight *0.07;
    }
    
    Rectangle AnioC;
    {
        AnioC.x=screenWidth *0.62;
        AnioC.y=screenHeight *0.27;
        AnioC.width = screenWidth *0.24;
        AnioC.height=screenHeight *0.07;
    }

    // ------ Datos Reales ------ //
    
    // Nombre real
    Rectangle NombreC;
    {
        NombreC.x= screenWidth * 0.14;
        NombreC.y=screenHeight *0.40;
        NombreC.width=screenWidth *0.7;
        NombreC.height = screenHeight * 0.07;
    }
   
    // Apellido Paterno
    Rectangle ApellidoPC;
    {
        ApellidoPC.x= screenWidth * 0.14;
        ApellidoPC.y=screenHeight *0.54;
        ApellidoPC.width=screenWidth *0.7;
        ApellidoPC.height = screenHeight * 0.07;
    }
   
    // Apellido materno
    Rectangle ApellidoC;
    {
        ApellidoC.x= screenWidth * 0.14;
        ApellidoC.y=screenHeight *0.66;
        ApellidoC.width=screenWidth *0.7;
        ApellidoC.height = screenHeight * 0.07;
    }

    // ------ Texto ------ //
    // Dia
    char dia[MaxCharacter +1]= {""};
    int diaCount=0;

    Vector2 diaV;
    diaV.x=DiaC.x+32;
    diaV.y=DiaC.y+20;
    
    // mes
    char mes[MaxCharacter +1]={""};
    int mesCount=0;

    Vector2 mesV;
    mesV.x=MesC.x+32;
    mesV.y=MesC.y+20;

    // Año
    char anio[MaxCharacter +1]={""};
    int anioCount=0;

    Vector2 anioV;
    anioV.x=AnioC.x+20;
    anioV.y=AnioC.y+20;

    // Nombre real
    char nombre[MaxCharacter+1]={""};
    int nombreCount=0;

    Vector2 nombreV;
    nombreV.x=NombreC.x+10;
    nombreV.y=NombreC.y+10;

    // Apellido paterno
    char apellidoP[MaxCharacter+1]={""};
    int apellidoPCount=0;

    Vector2 apellidoPV;
    apellidoPV.x=ApellidoPC.x+10;
    apellidoPV.y=ApellidoPC.y+10;
    
    // Apellido materno
    char apellidoM[MaxCharacter+1]={""};
    int apellidoMCount=0;
    
    Vector2 apellidoMV;
    apellidoMV.x=ApellidoC.x+10;
    apellidoMV.y=ApellidoC.y+10;

    while(finish3 == false){
        Mouse = GetMousePosition();
        BeginDrawing();
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click = Mouse;
            }
            
            // Fondo
            DrawTexture(background,0,0,WHITE);

            // ----- Dia ----- //
            if(CheckCollisionPointRec(Click,DiaC)){
                // se ilumina el cuadro que selecciono
                DrawRectangleRec(DiaC,selected);
                
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 48) && (key <= 57) && (diaCount < 2))
                    {
                        dia[diaCount] = (char)key;
                        dia[diaCount+1] = '\0'; 
                        diaCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (diaCount < 0){
                    } else{
                        diaCount--;   
                        dia[diaCount] = '\0'; 
                    }
                }
            }
            
            DrawTextEx(fuente,dia,diaV,24,1,BLACK);
            
            // ----- Mes ----- //
            DrawTextEx(fuente,mes,mesV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,MesC)){
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 48) && (key <= 57) && (mesCount < 2))
                    {
                        mes[mesCount] = (char)key;
                        mes[mesCount+1] = '\0'; 
                        mesCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (mesCount < 0){
                    } else{
                        mesCount--;   
                        mes[mesCount] = '\0'; 
                    }
                }
            }
            // ----- Anio ----- //
            DrawTextEx(fuente,anio,anioV,24,1,BLACK);
            
            if(CheckCollisionPointRec(Click,AnioC)){
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 48) && (key <= 57) && (anioCount < 4))
                    {
                        anio[anioCount] = (char)key;
                        anio[anioCount+1] = '\0'; 
                        anioCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (anioCount < 0){
                    } else{
                        anioCount--;   
                        anio[anioCount] = '\0'; 
                    }
                }
            }

            // ----- Nombre real ----- //

            DrawTextEx(fuente,nombre,nombreV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,NombreC)){
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (nombreCount < MaxCharacter))
                    {
                        nombre[nombreCount] = (char)key;
                        nombre[nombreCount+1] = '\0'; 
                        nombreCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (nombreCount < 0){
                    } else{
                        nombreCount--;   
                        nombre[nombreCount] = '\0'; 
                    }
                }
            }

            // ----- Apellido Paterno ----- //

            DrawTextEx(fuente,apellidoP,apellidoPV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,ApellidoPC)){
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (apellidoPCount < MaxCharacter))
                    {
                        apellidoP[apellidoPCount] = (char)key;
                        apellidoP[apellidoPCount+1] = '\0'; 
                        apellidoPCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (apellidoPCount < 0){
                    } else{
                        apellidoPCount--;   
                        apellidoP[apellidoPCount] = '\0'; 
                    }
                }
            }

            // ----- Apellido Materno ----- //
            DrawTextEx(fuente,apellidoM,apellidoMV,24,1,BLACK);

            if(CheckCollisionPointRec(Click,ApellidoC)){
                int key = GetCharPressed();
                while (key > 0) 
                {
                    if ((key >= 32) && (key <= 122) && (apellidoMCount < MaxCharacter))
                    {
                        apellidoM[apellidoMCount] = (char)key;
                        apellidoM[apellidoMCount+1] = '\0'; 
                        apellidoMCount++; 
                    }
                    key = GetCharPressed(); 
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if (apellidoMCount < 0){
                    } else{
                        apellidoMCount--;   
                        apellidoM[apellidoMCount] = '\0'; 
                    }
                }
            }

            // ----- Boton listo ----- //
            if(CheckCollisionPointRec(Click,ready)){
                finish3=true;
                ClearBackground(WHITE);
            }

        EndDrawing();
    }

    int id;
    user.UsuarioID=id;

    user.UserName=name;
    
    user.Passwoard=pas;
    user.Email=correo;
    user.Telefono=numero;
    
    user.Nombre=nombre;
    user.ApellidoPaterno=apellidoP;
    user.ApellidoMaterno=apellidoM;


    UnloadTexture(background);
    UnloadFont(fuente);

    return user;
}
