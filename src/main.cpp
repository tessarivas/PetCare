// BIBLIOTECAS
#include "raylib.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>   
#include <vector>
#include <time.h>
#include <algorithm>
#include <string.h>

// DEFINICIONES
#define ANCHO 414
#define ALTO 896

// ESTRCUTURAS
typedef enum Pantalla{
    INICIO = 0,
    CREAR_DUENO, // Donde se crea al dueño al entrar
    /*
    DUEÑO, // Perfil del dueño ya creado
    CREAR_MASCOTA,
    MASCOTA,
    INFO_MASCOTA,
    CARTILLAS_MASCOTA,
    CALENDARIO_MASCOTA
    */
} Pantalla;

// ESTRUCTURA PARA ARCHIVOS SUBIDOS
typedef struct Cargas{
    Texture2D FondoInicio;
} Cargas;

// FUNCIONES A IMPLEMENTAR:
// SUBIR IMAGENES, AUDIO, ETC...
Cargas CargarContenido(const char pantalla[], Cargas archivos);
//DIBUJAR PANTALLAS
void DibujarMenu(Pantalla pantalla_actual, Cargas archivos);
int DibujarInicio(Cargas archivos);
int DibujarCrearDueno(Cargas archivos);
int DibujarDueno(Cargas archivos);
int DibujarCrearMascota(Cargas archivos);
int DibujarMascota(Cargas archivos);
int DibujarInfoMascota(Cargas archivos);
int DibujarCartilla(Cargas archivos);
int DibujarCalendario(Cargas archivos);
// BAJAR IMAGENES, AUDIO, ETC...
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

// MENU PRINCIPAL
int main(){
    // CREAR VENTANA
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("resources/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // ASIGNAR PANTALLAS A VARIABLES
    Pantalla pantalla_actual = INICIO;
    Cargas archivos;
    archivos = CargarContenido("MENU", archivos);

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        // BOTONES PARA NAVEGAR ENTRE PANTALLAS
        int click1 = DibujarInicio(archivos);

        // CAMBIO DE PANTALLAS
        switch(pantalla_actual){
            case INICIO:
            {
                if(IsKeyPressed(KEY_SPACE) || click1 == 1){
                    pantalla_actual = CREAR_DUENO;
                    DescargarContenido(INICIO, archivos);
                    archivos = CargarContenido("CREAR_DUEÑO", archivos);
                }
            }
            break;
            case CREAR_DUENO:
            {
                printf("entro en crear");
            }
            break;
            default:
                break;
        }
        DibujarMenu(pantalla_actual, archivos);
    }

    // DESCARGAR CONTENIDO
    DescargarContenido(pantalla_actual, archivos);
    UnloadImage(icono);

    // CERRAR VENTANA
    CloseWindow();

    return 0;
}

// CARGAR TODAS LAS IMAGENES, AUDIO,FONTS, ETC...
Cargas CargarContenido(const char pantalla[], Cargas archivos){
    if(strcmp(pantalla, "INICIO") == 0){
        archivos.FondoInicio = LoadTexture("resources/PetCare_PantallaInicio.png");
    }
    if(strcmp(pantalla, "CREAR_DUENO")){
        archivos.FondoInicio = LoadTexture("resources/PetCare_PantallaInicio.png");
    }

    return archivos;
}

// DESCARGAR TODAS LAS IMAGENES, AUDIO,FONTS, ETC...
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos){
    if(pantalla_actual == INICIO){
        UnloadTexture(archivos.FondoInicio);
    }
    if(pantalla_actual == CREAR_DUENO){
        UnloadTexture(archivos.FondoInicio);
    }
}

// DIBUJAR LA PANTALLA DE INICIO CON LA QUE ENTRARA
int DibujarInicio(Cargas archivos){
    DrawTexturePro(
        archivos.FondoInicio,
        (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
        (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
        (Vector2){0, 0},
        0.0f,
    WHITE);

    return 0;
}

// DIBUJAR LA PANTALLA DE CREAR DUEÑO
int DibujarCrearDueno(Cargas archivos){
    DrawTexturePro(
        archivos.FondoInicio,
        (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
        (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
        (Vector2){0, 0},
        0.0f,
    WHITE);

    return 0;
}

// DIBUJAR MENU, PARA QUE SE PUEDA DESPLAZAR ENTRE PANTALLAS Y NO CARGAR TODO AL MISMO TIEMPO
void DibujarMenu(Pantalla pantalla_actual, Cargas archivos){
    // LIMPIAR PANTALLA
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // DIBUJAR ENTRE PANTALLAS
    switch(pantalla_actual){
        case INICIO:
        {
            DibujarInicio(archivos);
            break;
        }
        case CREAR_DUENO:
        {
            DibujarCrearDueno(archivos);
            break;
        }
        default:
            break;
    }

    EndDrawing();
}