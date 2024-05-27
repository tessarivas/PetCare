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


// ------------------Prototype------------------ //
void DibujarCalendario(Dog perro, int screenWidth, int screenHeight);

// ------------------Funciones------------------ //
// Dibujar papuCalendario
void DibujarCalendario(Dog perro, int screenWidth, int screenHeight){

    // Fondo
    Texture2D fondo = LoadTexture("../assets/Temp/calendario.png");
    Vector2 fondoPos;
    fondoPos.x=0;
    fondoPos.y=0;

    // Bandera de salida
    bool finish=false;

    //-------------------------Parte Superior------------------------------
    // titulo de calendario
    Rectangle TitleCalendario;
    TitleCalendario.x=screenWidth * 0.03;
    TitleCalendario.y=screenHeight * 0.03;
    TitleCalendario.width=screenWidth * 0.94;
    TitleCalendario.height=screenHeight * 0.07;

    // Titulo de mes
    Rectangle Mes;
    Mes.x=screenWidth*0.03;
    Mes.y=screenHeight * 0.13;
    Mes.width = screenWidth * 0.94;
    Mes.height = screenHeight * 0.03;

    // boton de mes anterior
    Rectangle PrevMonth;
    PrevMonth.x=screenWidth*0.03;
    PrevMonth.y=screenHeight*0.17;
    PrevMonth.width=screenWidth*0.13;
    PrevMonth.height=screenHeight*0.03;

    // Boton de siguiente mes
    Rectangle NextMonth;
    NextMonth.x=screenWidth*0.84;
    NextMonth.y=screenHeight*0.17;
    NextMonth.width=screenWidth*0.13;
    NextMonth.height=screenHeight*0.03;

    // Bloque de calendario
    Rectangle Calendario;
    Calendario.x=screenWidth * 0.03;
    Calendario.y=screenHeight*0.21;
    Calendario.width= screenWidth *0.95;
    Calendario.height= screenHeight * 0.70;

    // ----------------Evento--------------------------
    Rectangle titleEvent;
    titleEvent.x=screenWidth*0.1;
    titleEvent.y=screenHeight*0.61;
    titleEvent.width=screenWidth*0.80;
    titleEvent.height=screenHeight*0.07;

    Rectangle desEvent;
    desEvent.x=screenWidth*0.1;
    desEvent.y=screenHeight*0.69;
    desEvent.width=screenWidth*0.8;
    desEvent.height=screenHeight*0.19;

    // Agregar evento
    Rectangle Agregar;
    Agregar.x=screenWidth * 0.23;
    Agregar.y=screenHeight *0.84;
    Agregar.width=screenWidth * 0.54;
    Agregar.height=screenHeight * 0.08;

    //-----------------SALIR--------------------
    Rectangle Return;
    Return.x=screenWidth*0.03;
    Return.y=screenHeight * 0.93;
    Return.width=screenWidth * 0.2;
    Return.height = screenHeight * 0.05;

    
    //--------------------NUMERO DE DIAS-----------------------//
    /*
        13% de espacio entre el lado derecho
        7% de espacio entre los cubos de hacia abajo
    */

    
    //-------------------------------------------------------//

    Vector2 Mouse;
    Vector2 lastclick={0,0};

    // Slecciono un dia?
    bool daySelected = false;
    
    // El dia que selecciono
    int DiaSeleccionado;

    //------------CUADROS DE LOS DIAS-----------//
    float wi=0.05;
    float hi=0.27;
    Rectangle test;
    test.x=screenWidth*0.05;
    test.y=screenHeight*0.27;
    test.width=screenWidth*0.12;
    test.height=screenHeight*0.06;

    const int MaxCharacter=20;
    char title[MaxCharacter+1]={""};
    int titleCharacterCont=0;

    char des[MaxCharacter+1]={""};
    int desCharacterCont=0;


    while(finish == false){
        BeginDrawing();
            Mouse = GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                lastclick=Mouse;
            }

            // Fondo
            DrawTextureEx(fondo,fondoPos,0.0f,1.0f,WHITE);
            
            // Titulo de calendario
            DrawRectangleRec(TitleCalendario,RED);
            
            // titulo de Mes
            DrawRectangleRec(Mes,BLUE);

            // Mes anterior
            DrawRectangleRec(PrevMonth,RED);

            // Siguiente mes
            DrawRectangleRec(NextMonth,RED);

            // Cuadro de Calendario
            // DrawRectangleRec(Calendario,BLUE);
            
            
            // Evento-------------------------
            //titulo
            DrawRectangleRec(titleEvent,YELLOW);
            //Descripcion
            DrawRectangleRec(desEvent,YELLOW);

            // Tiene que seleccionar un dia para poder escribir un titulo y descripcion---
            if (daySelected== true)
            {
                if(CheckCollisionPointRec(lastclick,titleEvent))
                {
                    int key = GetCharPressed();
                    // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 122) && (titleCharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
                        {
                            title[titleCharacterCont] = (char)key; // Transformar el caracter de codigo ascii a caracter
                            title[titleCharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                            titleCharacterCont++; // Aumentamos el contador de caracteres
                        }
                        key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
                    {
                        if (titleCharacterCont < 0){
                            // Si la cadena esta vacia no hara nada
                        } else{
                            titleCharacterCont--; // Si no esta vacia eliminara un espacio     
                            title[titleCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                        }
                    }
                }
                
                if(CheckCollisionPointRec(lastclick,desEvent))
                {
                    int key = GetCharPressed();
                    // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 122) && (desCharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
                        {
                            des[desCharacterCont] = (char)key; // Transformar el caracter de codigo ascii a caracter
                            des[desCharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                            desCharacterCont++; // Aumentamos el contador de caracteres
                        }
                        key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
                    {
                        if (desCharacterCont < 0){
                            // Si la cadena esta vacia no hara nada
                        } else{
                            desCharacterCont--; // Si no esta vacia eliminara un espacio     
                            des[desCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                        }
                    }
                }
            }

            DrawText(title,titleEvent.x+10,titleEvent.y+10,24,BLACK);
            
            DrawText(des,desEvent.x+10,desEvent.y+10,24,BLACK);

            // Agregar evento------------------
            DrawRectangleRec(Agregar,RED);

            // Regresar
            DrawRectangleRec(Return,BLUE);

            if(CheckCollisionPointRec(lastclick,Return)){
                break;
            }
            
            wi=0.05;
            hi=0.27;
            test.x=screenWidth*0.05;
            test.y=screenHeight*0.27;
            

            // Esta funcion me costo musho alv y tan simple que esta
            /*
                Esta funcion creara un cuadro por cada dia del mes hasta 31,
                Primero dibujara 7 cuadros con separacion hacia la derecha de 13 %
                Luego reiniciara las posicion x a 0.05% y sumara la posicion y por 0.07% de la pantalla
                repetira el proceso cada que alcanze los 7 dias y asi hasta llegar a 31
                
                Una vez detecte que selecciono un cuadro que represente un dia, cambiara la bandera de daySelected a true
                y en otro ciclo, buscara en que ubicacion dio el click y que dia representa esa ubicacion, guardando el dia en
                diaSeleccionado
            */
            for(int i=1;i<=32;i++)
            {   
                if(CheckCollisionPointRec(lastclick,test))
                {
                    daySelected=true;
                }
                
                DrawRectangleRec(test,RED);
                
                if(i==8){
                    
                    wi = 0.05;
                    hi= hi + 0.07;
                    test.y=screenHeight * hi;
                }
                    
                if(i==15){
                    wi=0.05;
                    hi= hi + 0.07;
                    test.y=screenHeight * hi;
                }       
                        
                if(i==22){
                    wi=0.05;
                    hi= hi + 0.07;
                    test.y=screenHeight * hi;
                }

                if(i==29){
                    wi=0.05;
                    hi= hi + 0.07;
                    test.y=screenHeight * hi;
                }

                test.x=screenWidth * wi;
                test.y=screenHeight * hi;
                
                wi=wi+0.13;

            }

            if(daySelected== true)
            {
                wi=0.05;
                hi=0.27;
                test.x=screenWidth*0.05;
                test.y=screenHeight*0.27;
                for(int i=1;i<=32;i++)
                {   
                    
                    if(i==8){
                        wi = 0.05;
                        hi= hi + 0.07;
                        test.y=screenHeight * hi;
                    }
                        
                    if(i==15){
                        wi=0.05;
                        hi= hi + 0.07;
                        test.y=screenHeight * hi;
                    }       
                            
                    if(i==22){
                        wi=0.05;
                        hi= hi + 0.07;
                        test.y=screenHeight * hi;
                    }

                    if(i==29){
                        wi=0.05;
                        hi= hi + 0.07;
                        test.y=screenHeight * hi;
                    }

                    test.x=screenWidth * wi;
                    test.y=screenHeight * hi;

                    if(CheckCollisionPointRec(lastclick,test)){
                        DiaSeleccionado=i;
                        cout<<"DIA "<< DiaSeleccionado<<endl;
                    }
                    
                    wi=wi+0.13;
                }
            }

        EndDrawing();
    }
    UnloadTexture(fondo);
}
