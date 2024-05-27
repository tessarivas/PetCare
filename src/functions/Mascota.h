#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

#include "../clases/Usuario.h"
#include "Images.h"

// --------- Prototype ----------//
int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight);
Dog RegistrarDog(Cargas archivos, int screenWidth,int screenHeight);
Texture2D SeleccionarAvatarPerro(Cargas archivos,int screenWidth, int screenHeight);
void DibujarMisMascotas(Cargas archivos, int screenWidth, int screenHeight);

// --------- Functions ----------- //
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
            DrawRectangleRec(Cat, WHITE);
            DrawTextureEx(archivos.BotonGato, {Cat.x, Cat.y}, 0.0f, 1.0f, WHITE);
            DrawRectangleRec(Dog, WHITE);
            DrawTextureEx(archivos.BotonPerro, {Dog.x, Dog.y}, 0.0f, 1.0f, WHITE);

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

        EndDrawing();
    }
    return 0;
}

Dog RegistrarDog(Cargas archivos, int screenWidth,int screenHeight){
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
    // ATRAS
    Rectangle atras;
    atras.y = screenWidth * 0.05;
    atras.x = screenHeight * 0.03;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;

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
    
    // Bandera de ciclo
    bool band= false; 

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

        // Boton atras
        DrawTexture(archivos.BotonAtras, atras.x, atras.y, WHITE);
        /*
        // Verificar si se presiono atras
        if(CheckCollisionPointRec(LastClick, atras)){
            regresar = true;
            break;
        }
        */

        // Verificar que se hayan llenado los campos para avanzar adelante
        DrawTexture(archivos.BotonAdelante, adelante.x, adelante.y, WHITE);
        if(CheckCollisionPointRec(lastClick, adelante)){
            temp_name=name;
            temp_raza=raza;

            temp_dia = std::atoi(dia);
            temp_mes = std::atoi(mes);
            temp_anio = std::atoi(anio);
            
            temp_peso = std::atof(peso);
            temp_padecimientos = padecimientos;
            
            band = true;
        }

        // --------------- N O M B R E ---------------- //
        DrawRectangleRec(c_nombre, YELLOW);
        DrawText(name, c_nombre.x+10, c_nombre.y+10, 15, BLACK);
        
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
                }
                key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
            }
            if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
            {
                if (nameCharacterCont < 0){
                    // Si la cadena esta vacia no hara nada
                } else{
                    nameCharacterCont--; // Si no esta vacia eliminara un espacio     
                    name[nameCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                }
            }
        }

        // SE REPITE LO MISMO PARA CADA DATO INGRESADO DE LA MASCOTA:
        // ---------------- R A Z A ------------------- //
        DrawRectangleRec(c_raza,RED);
        DrawText(raza ,c_raza.x+10, c_raza.y+10, 15, BLACK);
        
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
                }
                key = GetCharPressed(); 
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if (razaCharacterCont < 0){
                } else{
                    razaCharacterCont--;   
                    raza[razaCharacterCont] = '\0'; 
                }
            }
        }
        
        // ----------------- D I A -------------------- //
        DrawRectangleRec(c_dia, YELLOW);
        DrawText(dia, c_dia.x+10, c_dia.y+10, 15, BLACK);
        
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
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if (diaCharacterCont < 0){
                } else{
                    diaCharacterCont--;   
                    dia[diaCharacterCont] = '\0'; 
                }
            }
        }

        // ----------------- M E S -------------------- //
        DrawRectangleRec(c_mes, YELLOW);
        DrawText(mes, c_mes.x+10, c_mes.y+10, 15, BLACK);

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
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (mesCharacterCont < 0){
                } else{
                    mesCharacterCont--;   
                    mes[mesCharacterCont] = '\0'; 
                }
            }
        }

        // ---------------- A N I O ------------------- //
        DrawRectangleRec(c_anio, YELLOW);
        DrawText(anio, c_anio.x+10, c_anio.y+10, 15, BLACK);

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
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if (anioCharacterCont < 0){
                } else{
                    anioCharacterCont--;     
                    anio[anioCharacterCont] = '\0';
                }
            }
        }

        // ---------------- P E S O ------------------- //
        DrawRectangleRec(c_peso, YELLOW);
        DrawText(peso, c_peso.x+10, c_peso.y+10, 15,BLACK);

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
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if (pesoCharacterCont < 0){
                } else{
                    pesoCharacterCont--;    
                    peso[pesoCharacterCont] = '\0'; 
                }
            }
        }

        //------------Padecimientos-----------------//
        DrawRectangleRec(c_padecimientos,GRAY);
        DrawText(padecimientos,c_padecimientos.x+10,c_padecimientos.y+10,15,BLACK);
        
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
                }
                key = GetCharPressed();  
            }
            if (IsKeyPressed(KEY_BACKSPACE)) 
            {
                if (padecimientosCharacterCont < 0){
                } else{
                    padecimientosCharacterCont--;    
                    padecimientos[padecimientosCharacterCont] = '\0'; 
                }
            }
        }

        EndDrawing();
    } while (band == false);

    Dog temp_dog(temp_name, temp_raza, temp_dia, temp_mes, temp_anio, temp_peso, temp_padecimientos);
    return temp_dog;
}

void DibujarMisMascotas(Cargas archivos, int screenWidth, int screenHeight){
    
    /* Faltaria agregar una forma de agregar las mascotas registradas, y ver cual de ellas selecciona
    Pero ya despues ;b*/
    
    Rectangle anadir;
    anadir.width = screenWidth * 0.55;
    anadir.height = screenHeight * 0.1;
    anadir.x=(screenWidth/2) - (anadir.width/2);
    anadir.y=screenHeight * 0.76;
    
    Vector2 Mouse;
    Vector2 LastClick;

    bool finish = false;

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

            // Verificar colision en boton añadir
            if(CheckCollisionPointRec(LastClick, anadir)){
                finish = true;
            }
            
        EndDrawing();
    }
}

Texture2D SeleccionarAvatarPerro(Cargas archivos,int screenWidth, int screenHeight){
    
    /*
        Maybe y la dejamos para el final

        Esta funcion es para que el usuario seleccione un avatar para el perro, devolvera una variable que tenga cargada la textura 
        de la mascota
    */
    
    bool finish = false;

    // HitBox De avatares
    // 1 renglon------------------
    Rectangle av1;
    av1.x= screenWidth * 0.18;
    av1.y= screenHeight * 0.32;
    av1.width= screenWidth * 0.3;
    av1.height= screenHeight * 0.13;
    
    Rectangle av2;
    av2.x= screenWidth * 0.50;
    av2.y= screenHeight * 0.32;
    av2.width= screenWidth * 0.3;
    av2.height= screenHeight * 0.13;
    // 2 renglon------------------
    Rectangle av3;
    av3.x= screenWidth * 0.18;
    av3.y= screenHeight * 0.46;
    av3.width= screenWidth * 0.3;
    av3.height= screenHeight * 0.13;
    
    Rectangle av4;
    av4.x= screenWidth * 0.50;
    av4.y= screenHeight * 0.46;
    av4.width= screenWidth * 0.3;
    av4.height= screenHeight * 0.13;
    // 3 renglon------------------
    Rectangle av5;
    av5.x= screenWidth * 0.18;
    av5.y= screenHeight * 0.60;
    av5.width= screenWidth * 0.3;
    av5.height= screenHeight * 0.13;
    
    Rectangle av6;
    av6.x= screenWidth * 0.50;
    av6.y= screenHeight * 0.60;
    av6.width= screenWidth * 0.3;
    av6.height= screenHeight * 0.13;

    // 4 renglon------------------
    Rectangle av7;
    av7.x= screenWidth * 0.18;
    av7.y= screenHeight * 0.74;
    av7.width= screenWidth * 0.3;
    av7.height= screenHeight * 0.13;
    
    Rectangle av8;
    av8.x= screenWidth * 0.50;
    av8.y= screenHeight * 0.74;
    av8.width= screenWidth * 0.3;
    av8.height= screenHeight * 0.13;

    Vector2 Mouse;
    Vector2 LastClick;

    // Texturas
    // Aqui la imagen
    // -------------- CAMBIAR IMAGENES -------------------------- //
    Texture2D av1_textura = LoadTexture("../assets/PetCare_avatares/1.png");
    Texture2D av2_textura = LoadTexture("../assets/PetCare_avatares/2.png");
    Texture2D av3_textura = LoadTexture("../assets/PetCare_avatares/3.png");

    while(finish == false){
        BeginDrawing();
            Mouse= GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                LastClick=Mouse;
            }

            //Fondo
            DrawTextureEx(archivos.Background, archivos.Position,0.0f,1.0f,WHITE);
            // Avatares
            //1er renglon
            DrawRectangleRec(av1, RED);
            DrawRectangleRec(av2, RED);
            // 2do renglon
            DrawRectangleRec(av3, BLUE);
            DrawRectangleRec(av4, BLUE);
            //3er renglon
            DrawRectangleRec(av5, RED);
            DrawRectangleRec(av6, RED);
            //4to renglon
            DrawRectangleRec(av7, BLUE);
            DrawRectangleRec(av8, BLUE);

            // Comprobacion de click en avatares
            if(CheckCollisionPointRec(LastClick,av1)){
                cout<<"selecciono el avatar 1"<<endl;
                /*
                    Unload texturas
                */
                return av1_textura;
            }
            if(CheckCollisionPointRec(LastClick,av2)){
                cout<<"selecciono el avatar 2"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av3)){
                cout<<"selecciono el avatar 3"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av4)){
                cout<<"selecciono el avatar 4"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av5)){
                cout<<"selecciono el avatar 5"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av6)){
                cout<<"selecciono el avatar 6"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av7)){
                cout<<"selecciono el avatar 7"<<endl;
            }
            if(CheckCollisionPointRec(LastClick,av8)){
                cout<<"selecciono el avatar 8"<<endl;
            }

        EndDrawing();
    }
    // Descargamos las texturas antes de salir de la funcion.
    UnloadTexture(av1_textura);
    
    // Esto solo pa que se quite el warning, al final nunca regresara este
    return av1_textura;
}

