// CartillaMedica.h

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::make_pair;

// EN ESTA FUNCION SE RELACIONA LA LIBRERIA DE Citas.h
#include "../clases/Usuario.h"

int DibujarCartillaMedica(Cita *citas, int screenWidth, int screenHeight);
pair<string, bool> DibujarAgregarCita(Cita **citasAgendadas, int screenWidth, int screenHeight);

int DibujarCartillaMedica(Cita *citas, int screenWidth, int screenHeight)
{
    // BANDERA PARA DETERMINAR SALIDA DE ESTA PANTALLA
    bool seleccion = false;

    // FONDO "MI_CARTILLA"
    Texture2D FondoMiCartilla = LoadTexture("../assets/PetCare_MiCartillaMedica.png");
    Vector2 Posicion = { 0.0f, 0.0f }; // Posicion
    // BOTON AGREGAR CITA
    Texture2D BotonAgregarCita = LoadTexture("../assets/PetCare_BotonAgregarCita.png");
    Rectangle AgregarCita;
    AgregarCita.width = screenWidth * 0.55;
    AgregarCita.height = screenHeight * 0.1;
    AgregarCita.y = screenHeight * 0.75;
    AgregarCita.x = (screenWidth / 2) - (AgregarCita.width / 2);
    // BOTON REGRESAR
    Texture2D BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
    Rectangle Atras;
    Atras.width = screenWidth * 0.55;
    Atras.height = screenHeight * 0.1;
    Atras.y = 20;
    Atras.x = 20;

    // Mouse y click
    Vector2 Mouse;
    Vector2 Click;

    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Click = Mouse;
        }

        // FondoMiCartilla Y BOTONES
        DrawTextureEx(FondoMiCartilla, Posicion, 0.0f, 1.0f, WHITE);
        DrawTexture(BotonAgregarCita, AgregarCita.x, AgregarCita.y, WHITE);
        DrawTexture(BotonAtras, Atras.x, Atras.y, WHITE);

        // Verificar si se presiono atras
        if(CheckCollisionPointRec(Click, Atras)){
            seleccion = true;
            UnloadTexture(FondoMiCartilla);
            UnloadTexture(BotonAgregarCita);
            UnloadTexture(BotonAtras);
            return 1;// No se como retornar bien
        }

        // Verificar si se presiono añadir, y dibujar la pantalla DIbujarAgregarCita
        // En el main implementaria que dependiendo el retorno cambie la pantalla.
        if(CheckCollisionPointRec(Click, AgregarCita)){
            seleccion = true;
            UnloadTexture(FondoMiCartilla);
            UnloadTexture(BotonAgregarCita);
            UnloadTexture(BotonAtras);
            return 1;// No se como retornar bien
        }

        EndDrawing();
    }while(seleccion == false);

    return 1; //No se que retornar
}

pair<string, bool> DibujarAgregarCita(Cita **citasAgendadas, int screenWidth, int screenHeight)
{
    // BANDERA PARA DETERMINAR EL CAMBIO DE ESTA PANTALLA
    bool regresar = false; // Para boton atras
    bool band = false; // Para boton agregar
    const int MaxCaracter = 20;
    int CuentaCaracteres = 0;
    int tamano_fondo = GetScreenWidth();

    char texto[MaxCaracter + 1] = "";
    string titulo;

    // FONDO "AGREGAR_CITA"
    Texture2D FondoMiCartilla = LoadTexture("../assets/PetCare_MiCartillaMedica.png");
    Vector2 Posicion = { 0.0f, 0.0f }; // Posicion
    // BOTON AÑADIR CITA
    Texture2D BotonAgregarCita = LoadTexture("../assets/PetCare_BotonAnadir.png");
    Rectangle Anadir;
    Anadir.width = screenWidth * 0.55;
    Anadir.height = screenHeight * 0.1;
    Anadir.y = screenHeight * 0.75;
    Anadir.x = (screenWidth / 2) - (Anadir.width / 2);
    // BOTON REGRESAR
    Texture2D BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
    Rectangle Atras;
    Atras.width = screenWidth * 0.55;
    Atras.height = screenHeight * 0.1;
    Atras.y = 20;
    Atras.x = 20;
    // CUADRO DE TEXTO TITULO
    Rectangle Titulo;
    Titulo.x = (tamano_fondo - 320 ) / 2;
    Titulo.y = 320.0f;
    Titulo.width = 320.0f;
    Titulo.height = 70.0f;
    // FUENTE DE LETRA
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // ME FALGTA IMPLEMENTAR RECUADROS DE TEXTO DE TITULO, DESCRIPCION Y FECHA PARA 
    // LAS CITAS QUE SE AGENDEN

    // Mouse y click
    Vector2 Mouse;
    Vector2 Click;

    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Click = Mouse;
        }

        // FondoMiCartilla Y BOTONES
        DrawTextureEx(FondoMiCartilla, Posicion, 0.0f, 1.0f, WHITE);
        DrawTexture(BotonAgregarCita, Anadir.x, Anadir.y, WHITE);
        DrawTexture(BotonAtras, Atras.x, Atras.y, WHITE);
        // RECTANGULO DEL NOMBRE
        DrawRectangleRec(Titulo, YELLOW);
        // CUADRO DE TEXTO
        Vector2 posicion_texto = {55, 325};
        DrawTextEx(fuente, texto, posicion_texto, 30, 2, BLACK);

        int tecla = GetCharPressed(); // Tecla presionada

        // VERIFICAR CLICK EN CUADRO DE TEXTO DEL TITULO
        if(CheckCollisionPointRec(Click, Titulo)){
            // Manejar la entrada de texto para el título de la cita
            while (tecla > 0){
                if ((tecla >= 32) && (tecla <= 125) && (CuentaCaracteres < MaxCaracter)){
                    texto[CuentaCaracteres] = (char)tecla;
                    texto[CuentaCaracteres + 1] = '\0';
                    CuentaCaracteres++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (CuentaCaracteres > 0){
                    texto[--CuentaCaracteres] = '\0';
                }
            }
        }

        // Verificar si se presiono atras y regresar a la pantalla que dibuja MiCartillaMedica
        if(CheckCollisionPointRec(Click, Atras)){
            regresar = true;
            break;
        }

        // Agregar la cita, al presionar botonanadir se regresa a la pantalla de MiCartillaMedica
        // Imprimir la cita agregada en mi cartilla medica.
        if(CheckCollisionPointRec(Click, Anadir)){
            band = true;
        }

        EndDrawing();
    }while(band == false);

    UnloadTexture(FondoMiCartilla);
    UnloadTexture(BotonAgregarCita);
    UnloadTexture(BotonAtras);

    titulo = texto;
    return make_pair(titulo, regresar); //No se que retornar
}
