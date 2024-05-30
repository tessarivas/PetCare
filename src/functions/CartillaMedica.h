// LIBRERIAS
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

/*
typedef enum Pantalla{
    MI_CARTILLA = 0,
    AGREGAR_CITA,
} Pantalla;

typedef struct Cargas{
    Texture2D FondoMiCartilla;
    Texture2D BotonAgregarCita;
    Texture2D FondoAgregarCita;
}
*/

// DECLARACION DE FUNCIONES
Evento *DibujarCartillaMedica(int screenWidth, int screenHeight);

// MI CARTILLA
Evento *DibujarCartillaMedica(int screenWidth, int screenHeight)
{
    bool regresar = false;

    Vector2 Mouse;
    Vector2 LastClick;

    Texture2D fondo = LoadTexture("../assets/PetCare_MiCartillaMedica.png");
    Vector2 fondoPos;
    fondoPos.x = 0;
    fondoPos.y = 0;

    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);


        Mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            LastClick = Mouse;
        }

        // FONDO Y BOTONES
        DrawTextureEx(fondo,fondoPos, 0.0f, 1.0f, WHITE); 

        EndDrawing();
    } while(regresar == false);

    UnloadTexture(fondo);
    return 0;
}
