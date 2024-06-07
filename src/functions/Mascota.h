#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 
#include "Images.h"

// --------- DECLARACION ----------//
int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight);
RegistrarDogResult RegistrarDog(Cargas archivos, int screenWidth,int screenHeight, Dog &temp_dog);
Texture2D SeleccionarAvatarPerro(Cargas archivos,int screenWidth, int screenHeight);
Dog DibujarMisMascotas(Cargas archivos, Dog *lista,Usuario user,int screenWidth, int screenHeight);
string SeleccionarGenero(Cargas archivos,int screenWidth,int screenHeight);

// --------- FUNCIONES ----------- //
int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight){
    //--------------Botones----------------//
    // Boton atras
    Rectangle atras;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;
    atras.y = 20;
    atras.x = 20;
    
    // Boton de gato
    Rectangle Cat;
    //Posicion
    Cat.x = screenWidth * 0.1; // El 10% de la pantalla
    Cat.y = screenHeight * 0.36;
    // Largo y ancho
    Cat.width = screenWidth * 0.79;
    Cat.height = 120;
    
    // Boton de perro
    Rectangle Dog;
    //Posicion
    Dog.x = screenWidth * 0.1; // El 10% de la pantalla
    Dog.y = screenHeight * 0.56; // Un 20% más abajo
    // Largo y ancho
    Dog.width = screenWidth * 0.79;
    Dog.height = 120;

    // Posicion del boton de link
    Vector2 linkV;
    linkV.x=(screenWidth / 2) - ((archivos.BotonLink.width * 0.7) / 2) + 10;
    linkV.y = screenHeight * 0.76;

    // hitbox del boton de link
    Rectangle linkC;
    linkC.x=linkV.x;
    linkC.y=linkV.y;
    linkC.width=archivos.BotonLink.width * 0.7;
    linkC.height=archivos.BotonLink.height;

    //----------Otras variables--------------//
    //Posicion actual del mouse
    Vector2 Mouse = {0.0f, 0.0f};

    bool ciclo = true;

    // Puedes usar la posicion del rectangulo para poner la imagen de los botones
    while (ciclo == true){
        Mouse = GetMousePosition();
        
        BeginDrawing();
            ClearBackground(RAYWHITE); // Limpia la pantalla con un color de fondo
            DrawTextureEx(archivos.FondoAnadirMascotas, archivos.Position, 0.0f, 1.0f, WHITE);

            // Boton átras
            DrawTexture(archivos.BotonAtras, atras.x, atras.y, WHITE);

            //Botones Posicion
            DrawTextureEx(archivos.BotonGato, {Cat.x, Cat.y}, 0.0f, 1.0f, WHITE);
            
            DrawTextureEx(archivos.BotonPerro, {Dog.x, Dog.y}, 0.0f, 1.0f, WHITE);

            DrawTextureEx(archivos.BotonLink,linkV,0.0f,0.6f,WHITE);

            // Comparar las posiciones del mouse con un rectangulo
            // SI PRESIONA GATO:
            if (CheckCollisionPointRec(Mouse, Cat) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ciclo = false;
                return 1;
            }
            // SI PRESIONA PERRO:
            if (CheckCollisionPointRec(Mouse, Dog) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ciclo = false;
                return 2;
            }
            // SI PRESIONA ATRAS:
            if (CheckCollisionPointRec(Mouse, atras) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ciclo = false;
                return 3;
            }
            
            if (CheckCollisionPointRec(Mouse, linkC) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // tiempo
                float timetolive = 2.0f;
                float actualtime = 0.0f;
                
                while(actualtime <= timetolive){
                    actualtime +=GetFrameTime();
                    BeginDrawing();
                        DrawTexture(archivos.FuncionNoDisponible,0,0,WHITE);
                        
                        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE)){
                            break;
                        }
                    EndDrawing();
                }
            }

        EndDrawing();
    }
    return 0;
}

RegistrarDogResult RegistrarDog(Cargas archivos, int screenWidth,int screenHeight, Dog &temp_dog){
    // Nombre
    Rectangle c_nombre;
    c_nombre.x=screenWidth * 0.1; // 10% de espacio entre el borde de la izquierda
    c_nombre.y=screenHeight * 0.3; // 30% de espacio entre el borde de arriba
    c_nombre.width = screenWidth * 0.78; // 78% de tamanio de la pantalla medira el cuadro de ancho
    c_nombre.height = 40; // 40px medira el cuadro
    // --------------------------------------------- //
    // Raza
    Rectangle c_raza;
    c_raza.x=screenWidth * 0.1;
    c_raza.y=screenHeight * 0.42;
    c_raza.width = screenWidth * 0.78;
    c_raza.height = 40;
    // --------------------------------------------- //
    // FECHA
    Rectangle c_dia;
    Rectangle c_mes;
    Rectangle c_anio;
    // DIA
    c_dia.x=screenWidth * 0.1;
    c_dia.y=screenHeight * 0.53;
    c_dia.width= screenWidth * 0.25;
    c_dia.height = 40;
    // MES
    c_mes.x=screenWidth * 0.36;
    c_mes.y=screenHeight * 0.53;
    c_mes.width= screenWidth * 0.26;
    c_mes.height = 40;
    // AÑO
    c_anio.x=screenWidth * 0.63;
    c_anio.y=screenHeight * 0.53;
    c_anio.width= screenWidth * 0.25;
    c_anio.height = 40;
    // --------------------------------------------- //
    // PESO
    Rectangle c_peso;
    c_peso.x=screenWidth * 0.1;
    c_peso.y=screenHeight * 0.65;
    c_peso.width = screenWidth * 0.78;
    c_peso.height = 40;
    // --------------------------------------------- //
    // PADECIMIENTOS
    Rectangle c_padecimientos;
    c_padecimientos.x=screenWidth * 0.1;
    c_padecimientos.y=screenHeight * 0.75;
    c_padecimientos.width = screenWidth * 0.78;
    c_padecimientos.height = 40;
    // --------------------------------------------- //
    // ADELANTE/SIGUIENTE
    Rectangle adelante;
    adelante.x = screenWidth * 0.85;
    adelante.y = screenHeight * 0.03;
    adelante.width = screenWidth * 0.1;
    adelante.height = screenHeight * 0.05;
    // --------------------------------------------- //
    // BOTON ATRAS
    Rectangle atras;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;
    atras.y = 20;
    atras.x = 20;

    // Variables temporales de cada dato
    string temp_name;
    string temp_raza;
    int temp_dia;
    int temp_mes;
    int temp_anio;
    float temp_peso;
    string temp_padecimientos;

    // Manejo de clicks
    Vector2 Mouse;
    Vector2 lastClick;

    // Maximo de caracteres
    const int MaxCharacter=20;
    // Cadena que almacenara caracter por caracter, +1 por el caracter nulo
    char name[MaxCharacter+1]={""};
    char raza[MaxCharacter+1]={""};
    char dia[MaxCharacter+1]={""};
    char mes[MaxCharacter+1]={""};
    char anio[MaxCharacter+1]={""};
    char peso[MaxCharacter+1]={""};
    char padecimientos[MaxCharacter+1]={""};
    
    //Contador de caracteres actuales
    int nameCharacterCont=0;
    int razaCharacterCont=0;
    int diaCharacterCont=0;
    int mesCharacterCont=0;
    int anioCharacterCont=0;
    int pesoCharacterCont=0;
    int padecimientosCharacterCont=0;
    
    // Posicion de texto
    Vector2 namePos;
    namePos.x=c_nombre.x+10;
    namePos.y=c_nombre.y+10;

    Vector2 razaPos;
    razaPos.x=c_raza.x + 10;
    razaPos.y=c_raza.y + 10;

    Vector2 diaPos;
    diaPos.x=c_dia.x+10;
    diaPos.y=c_dia.y+10;

    Vector2 mesPos;
    mesPos.x=c_mes.x+10;
    mesPos.y=c_mes.y+10;
    
    Vector2 anioPos;
    anioPos.x=c_anio.x+10;
    anioPos.y=c_anio.y+10;

    Vector2 pesoPos;
    pesoPos.x=c_peso.x+10;
    pesoPos.y=c_peso.y+10;

    Vector2 padePos;
    padePos.x=c_padecimientos.x+10;
    padePos.y=c_padecimientos.y+10;

    // Bandera de ciclo
    bool band= false; 
    RegistrarDogResult result = CONTINUAR;

    bool namefull=false;
    bool razafull=false;
    bool diafull=false;
    bool mesfull=false;
    bool aniofull=false;
    bool pesofull=false;
    bool padefull=false;

    do
    {
        BeginDrawing();
        
        // Fondo
        DrawTextureEx(archivos.FondoRegPerro,archivos.Position,0.0f,1.0f,WHITE);
        
        // Obtiene la posicion actual de mouse
        Mouse = GetMousePosition();
        // Este almacenara la ultima posicion de donde hizo click
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            lastClick = Mouse;
        }        

        DrawTexture(archivos.BotonAtras, atras.x, atras.y, WHITE);
        if (CheckCollisionPointRec(lastClick, atras)) {
            result = REGRESAR;
            break;
        }

        // Verificar que se hayan llenado los campos para avanzar adelante
        DrawTexture(archivos.BotonAdelante, adelante.x, adelante.y, WHITE);
        if(CheckCollisionPointRec(lastClick, adelante))
        {
            if(namefull && razafull && diafull && mesfull && aniofull && pesofull && padefull){
                temp_name=name;
                temp_raza=raza;

                temp_dia = std::atoi(dia);
                temp_mes = std::atoi(mes);
                temp_anio = std::atoi(anio);
                
                temp_peso = std::atof(peso);
                temp_padecimientos = padecimientos;

                temp_dog = Dog(temp_name, temp_raza, temp_dia, temp_mes, temp_anio, temp_peso, temp_padecimientos);
                
                band = true;
                result = AVANZAR;
            }
            else
            {
                LlenarCampos();
                lastClick = {0,0};
            }
        }

        // --------------- N O M B R E ---------------- //
        // Cuadro
        DrawRectangleRec(c_nombre, archivos.Bloque1);
        // Texto en pantalla
        DrawTextEx(archivos.fuente,name,namePos,18,1,BLACK);
        
        // Colision con cuadro de texto de nombre
        if(CheckCollisionPointRec(lastClick,c_nombre))
        {
            int key = GetCharPressed();
            // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
            while (key > 0)
            {
                if ((key >= 32) && (key <= 122) && (nameCharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
                {
                    name[nameCharacterCont] = (char)key; // Transformar el caracter de codigo ascii a caracter
                    name[nameCharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                    nameCharacterCont++; // Aumentamos el contador de caracteres
                    namefull=true;
                }
                key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
            }
            if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
            {
                if(nameCharacterCont <=1){
                    namefull = false;
                }
                if (nameCharacterCont <= 0){
                    // Si la cadena esta vacia no hara nada
                } else{
                    nameCharacterCont--; // Si no esta vacia eliminara un espacio     
                    name[nameCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                }
            }
        }

        // SE REPITE LO MISMO PARA CADA DATO INGRESADO DE LA MASCOTA:
        // ---------------- R A Z A ------------------- //
        // Cuadro
        DrawRectangleRec(c_raza,archivos.Bloque1);
        // Texto en pantalla
        DrawTextEx(archivos.fuente,raza,razaPos,18,1,BLACK);
        
        if(CheckCollisionPointRec(lastClick,c_raza))
        {
            int key = GetCharPressed();
            while (key > 0) 
            {
                if ((key >= 32) && (key <= 122) && (razaCharacterCont <MaxCharacter))
                {
                    raza[razaCharacterCont] = (char)key;
                    raza[razaCharacterCont+1] = '\0'; 
                    razaCharacterCont++; 
                    razafull = true;
                }
                key = GetCharPressed(); 
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if(razaCharacterCont <=1){
                    razafull = false;
                }
                if (razaCharacterCont <= 0){
                } else{
                    razaCharacterCont--;   
                    raza[razaCharacterCont] = '\0'; 
                }
            }
        }
        
        // ----------------- D I A -------------------- //
        DrawRectangleRec(c_dia, archivos.Bloque1);
        
        DrawTextEx(archivos.fuente,dia,diaPos,18,1,BLACK);
        
        if(CheckCollisionPointRec(lastClick,c_dia))
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 48) && (key <= 57) && (diaCharacterCont <MaxCharacter)) 
                {
                    dia[diaCharacterCont] = (char)key; 
                    dia[diaCharacterCont+1] = '\0'; 
                    diaCharacterCont++; 
                    diafull = true;
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if(diaCharacterCont <=1){
                    diafull=false;
                }
                if (diaCharacterCont <= 0){
                } else{
                    diaCharacterCont--;   
                    dia[diaCharacterCont] = '\0'; 
                }
            }
        }

        // ----------------- M E S -------------------- //
        DrawRectangleRec(c_mes, archivos.Bloque1);
        
        DrawTextEx(archivos.fuente,mes,mesPos,18,1,BLACK);

        if(CheckCollisionPointRec(lastClick,c_mes))
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 48) && (key <= 57) && (mesCharacterCont <MaxCharacter))
                {
                    mes[mesCharacterCont] = (char)key; 
                    mes[mesCharacterCont+1] = '\0';
                    mesCharacterCont++; 
                    mesfull=true;
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if(mesCharacterCont <=1){
                    mesfull = false;
                }
                if (mesCharacterCont <= 0){
                } else{
                    mesCharacterCont--;   
                    mes[mesCharacterCont] = '\0'; 
                }
            }
        }

        // ---------------- A N I O ------------------- //
        DrawRectangleRec(c_anio, archivos.Bloque1);
        
        DrawTextEx(archivos.fuente,anio,anioPos,18,1,BLACK);

        if(CheckCollisionPointRec(lastClick,c_anio))
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 48) && (key <= 57) && (anioCharacterCont <MaxCharacter)) 
                {
                    anio[anioCharacterCont] = (char)key; 
                    anio[anioCharacterCont+1] = '\0'; 
                    anioCharacterCont++; 
                    aniofull=true;
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if(anioCharacterCont <=1){
                    aniofull = false;
                }
                if (anioCharacterCont <= 0){
                } else{
                    anioCharacterCont--;     
                    anio[anioCharacterCont] = '\0';
                }
            }
        }

        // ---------------- P E S O ------------------- //
        DrawRectangleRec(c_peso, archivos.Bloque1);
        
        DrawTextEx(archivos.fuente,peso,pesoPos,18,1,BLACK);

        if(CheckCollisionPointRec(lastClick,c_peso))
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 46) && (key <= 57) && (pesoCharacterCont <MaxCharacter)) 
                {
                    peso[pesoCharacterCont] = (char)key;
                    peso[pesoCharacterCont+1] = '\0'; 
                    pesoCharacterCont++; 
                    pesofull=true;
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if(pesoCharacterCont <=1){
                    pesofull = false;
                }
                if (pesoCharacterCont <= 0){
                } else{
                    pesoCharacterCont--;    
                    peso[pesoCharacterCont] = '\0'; 
                }
            }
        }

        //------------Padecimientos-----------------//
        DrawRectangleRec(c_padecimientos,archivos.Bloque1);
        
        DrawTextEx(archivos.fuente,padecimientos,padePos,18,1,BLACK);
        
        if(CheckCollisionPointRec(lastClick,c_padecimientos))
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 122) && (padecimientosCharacterCont <MaxCharacter)) 
                {
                    padecimientos[padecimientosCharacterCont] = (char)key; 
                    padecimientos[padecimientosCharacterCont+1] = '\0'; 
                    padecimientosCharacterCont++; 
                    padefull=true;
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if(padecimientosCharacterCont <=1){
                    padefull = false;
                }
                if (padecimientosCharacterCont <= 0){
                } else{
                    padecimientosCharacterCont--;    
                    padecimientos[padecimientosCharacterCont] = '\0'; 
                }
            }
        }

        EndDrawing();
    } while (band == false);

    return result;
}

Dog DibujarMisMascotas(Cargas archivos, Dog *lista,Usuario user,int screenWidth, int screenHeight){
    
    Rectangle anadir;
    anadir.width = screenWidth * 0.55;
    anadir.height = screenHeight * 0.1;
    anadir.x=(screenWidth/2) - (anadir.width/2);
    anadir.y=screenHeight * 0.76;
    
    Vector2 Mouse;
    Vector2 LastClick;

    bool finish = false;

    Dog *temp=lista;
    char name[30];
    char raza[30];

    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    Color Bloque={245,246,243,255};

    Vector2 textPos;
    textPos.x=screenWidth * 0.10;
    textPos.y=screenHeight * 0.20;
    
    Vector2 avatarPos;
    avatarPos.x=screenWidth * 0.70;
    avatarPos.y=textPos.y;

    Rectangle DogBox;
    DogBox.x=textPos.x-10;
    DogBox.y=textPos.y-10;
    DogBox.width=screenWidth *0.85;
    DogBox.height=screenHeight *0.12;

    // texto del nombre del dueno
    int nameSize= MeasureText(user.UserName.c_str(),20);

    Vector2 UserNameV;
    UserNameV.x=(screenWidth / 2) - (nameSize/2);
    UserNameV.y=screenHeight *0.93;

    // Posicion del avatar del dueno
    Vector2 UserAvatarV;
    UserAvatarV.x=UserNameV.x-80;
    UserAvatarV.y=screenHeight *0.90;

    Dog selected;

    while (finish == false)
    {
        BeginDrawing();
            // Posicion actual de mouse
            Mouse= GetMousePosition();
            
            // Posicion del ultimo click
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                LastClick= Mouse;
            }
            
            // Fondo
            DrawTextureEx(archivos.FondoMisMascotas,archivos.Position,0.0f,1.0f,WHITE);
            
            // Boton de anadir
            DrawTexture(archivos.BotonAnadir, anadir.x, anadir.y, WHITE);

            // -------- Lista ---------//
            temp=lista;
            textPos.x=screenWidth * 0.10;
            textPos.y=screenHeight * 0.20;
            
            avatarPos.x=screenWidth * 0.70;
            avatarPos.y=textPos.y;

            DogBox.x=textPos.x-10;
            DogBox.y=textPos.y-10;
            DogBox.width=screenWidth *0.85;
            DogBox.height=screenHeight *0.14;
            
            while(temp != nullptr){
                // cout<< "Entro aqui con "<<temp->Nombre<<endl;
                
                // Pasamos los valores a char -----
                    strcpy(name,temp->Nombre.c_str());
                    strcpy(raza,temp->Raza.c_str());

                // volvemos a definir el hitbox
                    DogBox.x=textPos.x-10;
                    DogBox.y=textPos.y-10;
                    DogBox.width=screenWidth *0.85;
                    DogBox.height=screenHeight *0.12;
                
                // Comenzamos a dibujar
                DrawRectangleRec(DogBox,Bloque);

                DrawTextEx(fuente,name,textPos,34,2,BLACK);

                DrawTextureEx(temp->Avatar,avatarPos,0.0f,1.0f,WHITE);
        
                textPos.y+=34;
                DrawTextEx(fuente,raza,textPos,34,2,BLACK);
                
                // Colisiones
                if(CheckCollisionPointRec(LastClick,DogBox)){
                    selected = *temp;
                    finish=true;
                }
                
                // pasamos al siguiente registro
                temp=temp->next;
                // Al final una separacion de 54 pixeles entre cada registro
                textPos.y+=85;
                avatarPos.y+=115;

            }
            
            // Verificar colision en boton añadir
            if(CheckCollisionPointRec(LastClick, anadir)){
                finish = true;
                return selected;
            }

            DrawTextureEx(user.avatar,UserAvatarV,0.0f,1.0f,WHITE);

            const char *nombre = user.UserName.c_str();
            
            DrawTextEx(fuente,nombre,UserNameV,32,1,BLACK);
            
        EndDrawing();
    }    
    
    return selected;
}

Texture2D SeleccionarAvatarPerro(Cargas archivos,int screenWidth, int screenHeight)
{
    int avatarSeleccionado = -1;

    Rectangle AvatarPerro[8];
    Texture2D avatarPerroTextura[8] = { archivos.PERRO1, archivos.PERRO2, archivos.PERRO3, archivos.PERRO4, archivos.PERRO5, archivos.PERRO6, archivos.PERRO7, archivos.PERRO8};

    // Definir posiciones de los avatares
    for(int i = 0; i < 8; i++){
        AvatarPerro[i].x = screenWidth * ((i % 2 == 0) ? 0.18f : 0.60f);
        AvatarPerro[i].y = screenHeight * (0.32f + (0.14f * (i / 2)));
        AvatarPerro[i].width = screenWidth * 0.3f;
        AvatarPerro[i].height = screenHeight * 0.13f;
    }

    Vector2 Mouse;
    Vector2 LastClick;

    // MIENTRAS QUE NO SE HAYA SELECCIONADO NINGUN AVATAR
    while (avatarSeleccionado == -1){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // OBTENER POSICION DEL MOUSE
        Mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            LastClick = Mouse;
        }

        // FONDO DE LA PANTALLA
        DrawTextureEx(archivos.Background, archivos.Position,0.0f,1.0f,WHITE);

        // VERIFICAR EL CLICK EN EL AVATAR
        for(int i = 0; i < 8; i++){
            if (CheckCollisionPointRec(LastClick, AvatarPerro[i])){
                avatarSeleccionado = i;
                break;
            }
        }

        // DIBUJAR AVATAR Y BORDE DEL QUE SELECCIONEN
        for(int i = 0; i < 8; i++){
            DrawTextureEx(avatarPerroTextura[i], { AvatarPerro[i].x, AvatarPerro[i].y }, 0.0f, 1.0f, WHITE);
            if (avatarSeleccionado == i){
                DrawRectangleLinesEx(AvatarPerro[i], 8, GREEN);
            }
        }

        EndDrawing();
    }

    // Retornar la textura del avatar seleccionado
    return avatarPerroTextura[avatarSeleccionado];
}

string SeleccionarGenero(Cargas archivos,int screenWidth,int screenHeight){
    bool finish = false;

    Rectangle FemeninoC;
    FemeninoC.x=screenWidth *0.15;
    FemeninoC.y=screenHeight *0.32;
    FemeninoC.width = screenWidth *0.7;
    FemeninoC.height = screenHeight *0.12;

    Rectangle MasculinoC;
    MasculinoC.x=screenWidth *0.15;
    MasculinoC.y=screenHeight *0.60;
    MasculinoC.width = screenWidth *0.7;
    MasculinoC.height = screenHeight *0.12;

    Vector2 Mouse;
    Vector2 Click;

    while(finish == false){
        BeginDrawing();
            Mouse=GetMousePosition();
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click=Mouse;
            }

            DrawTexture(archivos.FondoGenero,0,0,WHITE);
            
            if(CheckCollisionPointRec(Click,FemeninoC)){
                string F = "F";
                return F;
            }
            
            if(CheckCollisionPointRec(Click,MasculinoC)){
                string M = "M";
                return M;
            }            

        EndDrawing();
    }
}
