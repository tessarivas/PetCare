// BIBLIOTECAS
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// DEFINICIONES
#define ANCHO 414
#define ALTO 896

// ESTRCUTURAS
typedef enum Pantalla{
    INICIO = 0,
    CREAR_DUENO, // Donde se crea al dueño al entrar
    MIS_MASCOTAS,
    CREAR_MASCOTA,
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
    Vector2 Position;
} Cargas;

// FUNCIONES A IMPLEMENTAR:
// SUBIR IMAGENES, AUDIO, ETC...
Cargas CargarContenido(Pantalla actual, Cargas archivos);
//DIBUJAR PANTALLAS
void DibujarMenu(Pantalla pantalla_actual, Cargas archivos);
int DibujarInicio(Cargas archivos);
int DibujarCrearDueno(Cargas archivos);
// int DibujarDueno(Cargas archivos);
// int DibujarCrearMascota(Cargas archivos);
// int DibujarMascota(Cargas archivos);
// int DibujarInfoMascota(Cargas archivos);
// int DibujarCartilla(Cargas archivos);
// int DibujarCalendario(Cargas archivos);
// BAJAR IMAGENES, AUDIO, ETC...
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

// Functions
void DibujarMisMascotas(Cargas archivos);
void DibujarCrearMascota(Cargas archivos);
void DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight);

// MENU PRINCIPAL
int main(){
    // CREAR VENTANA
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    // Ruta
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // ASIGNAR PANTALLAS A VARIABLES
    Pantalla pantalla_actual = INICIO;
    Cargas archivos;
    archivos = CargarContenido(pantalla_actual, archivos);

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        // BOTONES PARA NAVEGAR ENTRE PANTALLAS
        int click1 = DibujarInicio(archivos);

        // CAMBIO DE PANTALLAS
        switch(pantalla_actual)
        {
            case INICIO:
            {
                DibujarMenu(pantalla_actual, archivos);
                if(IsKeyPressed(KEY_SPACE) || click1 == 1){
                    // Primero descargar la pantalla actual
                    DescargarContenido(pantalla_actual, archivos); //En vez de tener que enviar una cadena podemos solamente enviar la pantalla
                    // Actualizamos la variable que representa la pantalla
                    pantalla_actual = CREAR_DUENO;
                    // Actualizamos la textura
                    archivos = CargarContenido(pantalla_actual, archivos);
                }
                break;
            }
            case CREAR_DUENO:
            {
                DibujarCrearPerfil(archivos,ANCHO,ALTO);
                if(IsKeyPressed(KEY_SPACE) || click1 == 1){
                    DescargarContenido(pantalla_actual, archivos);
                    pantalla_actual = MIS_MASCOTAS;
                    archivos = CargarContenido(pantalla_actual, archivos);
                }
                break;
            }
            case MIS_MASCOTAS:
            {
                if(IsKeyPressed(KEY_SPACE) || click1 == 1){
                    DescargarContenido(pantalla_actual, archivos);
                    pantalla_actual = CREAR_MASCOTA;
                    archivos = CargarContenido(pantalla_actual, archivos);
                }
                break;
            }
            case CREAR_MASCOTA:
            {
                if(IsKeyPressed(KEY_SPACE) || click1 == 1){
                    DescargarContenido(pantalla_actual, archivos);
                    pantalla_actual = CREAR_MASCOTA;
                    archivos = CargarContenido(pantalla_actual, archivos);
                }
                break;
            }
            break;
            default:
                break;
        }
        // DibujarMenu(pantalla_actual, archivos);
    }

    // DESCARGAR CONTENIDO
    DescargarContenido(pantalla_actual, archivos);
    UnloadImage(icono);

    // CERRAR VENTANA
    CloseWindow();

    return 0;
}

// CARGAR TODAS LAS IMAGENES, AUDIO,FONTS, ETC...
Cargas CargarContenido(Pantalla actual, Cargas archivos){
    
    switch (actual)
    {
        case INICIO:
        {
            archivos.FondoInicio = LoadTexture("../assets/PetCare_PantallaInicio.png");
            archivos.Position.x=0;
            archivos.Position.y=0;
            break;
        }
        case CREAR_DUENO:
        {
            archivos.FondoInicio = LoadTexture("../assets/CrearDuenoPreview.png");
            break;
        }
        case MIS_MASCOTAS:
        {
            archivos.FondoInicio=LoadTexture("./assets/MisMascotas.png");
            break;
        }
        case CREAR_MASCOTA:
        {
            archivos.FondoInicio=LoadTexture("../assets/AnadirMascota.png");
            break;
        }
        default:
            break;
    }

    return archivos;
}

// DESCARGAR TODAS LAS IMAGENES, AUDIO,FONTS, ETC...
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos){
    UnloadTexture(archivos.FondoInicio);
}

// DIBUJAR LA PANTALLA DE INICIO CON LA QUE ENTRARA
int DibujarInicio(Cargas archivos){
    // DrawTexturePro(
    //     archivos.FondoInicio,
    //     (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
    //     (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
    //     (Vector2){0, 0},
    //     0.0f,
    // WHITE);
    DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.0f,WHITE);
    
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

void DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight){
    const int MaxCharacter=20;
    int CharacterCont=0;
    char name[MaxCharacter+1];

    do
    {
        BeginDrawing();
        DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.6f,WHITE);
        ClearBackground(WHITE);
        DrawRectangle(50.0f,320.0f,320.0f,70.0f,GRAY);
        DrawText(name,55,325,30,BLACK);
        
        int key = GetCharPressed();

        // Verificar si hay presiona mas de 1 caracter en el mismo frame
        // Saldra del ciclo si no presiona nada
        while (key > 0)
        {
            // Solo caracteres entre el 32 y 125
            if ((key >= 32) && (key <= 125) && (CharacterCont <MaxCharacter))
            {
                name[CharacterCont] = (char)key; //transformar el caracter de codigo asci a caracter
                name[CharacterCont+1] = '\0'; //Agregar caracter nulo al final de la cadena
                CharacterCont++; //Aumentamso el contador de caracteres
            }

            key = GetCharPressed();  // revisamos si hay nuevos caracteres en cola
        }

        if (IsKeyPressed(KEY_BACKSPACE)) //Borrar
        {
            // Si la cadena esta vacia no hara nada
            if (CharacterCont < 0){
                // No hace nada
            }
            else //Si no esta vacia eliminara un espacio
            {
                CharacterCont--;     
            }
            name[CharacterCont] = '\0'; //Al ultimo que antes era una letra la sustituimos por el caracter nulo
        }
        if (IsKeyPressed(KEY_ESCAPE)){
            break;
        }
        EndDrawing();
    } while (true);
}

void DibujarMisMascotas(Cargas archivos){
    DrawTexturePro(
        archivos.FondoInicio,
        (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
        (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
        (Vector2){0, 0},
        0.0f,
    WHITE);
}

void DibujarCrearMascota(Cargas archivos){
    
    DrawTexturePro(archivos.FondoInicio,
        (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
        (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
        (Vector2){0, 0},
        0.0f,
    WHITE);
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
        case MIS_MASCOTAS:
        {
            DibujarMisMascotas(archivos);
        }
        case CREAR_MASCOTA:
        {
            DibujarCrearMascota(archivos);
        }
        default:
            break;
    }

    EndDrawing();
}