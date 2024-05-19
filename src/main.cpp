#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

#include "classes/Usuario.h"

using std::cout;
using std::endl;
using std::string;


// DEFINICIONES
#define ANCHO 414
#define ALTO 896

//---------------------Escenarios------------------------------------------------
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

//----------------------Images----------------------------------------------------
typedef struct Cargas{
    Texture2D FondoInicio;
    Vector2 Position;
} Cargas;

//------------------Load And Unload Content----------------------------------------
Cargas CargarContenido(Pantalla actual, Cargas archivos);
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

//-----------------------Draw Screen-----------------------------------------------
void DibujarMenu(Pantalla pantalla_actual, Cargas archivos);
int DibujarInicio(Cargas archivos);
int DibujarCrearDueno(Cargas archivos);

//-----------------------Extra Functions-------------------------------------------
void DibujarMisMascotas(Cargas archivos);
void DibujarCrearMascota(Cargas archivos);
string DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight);

//-------------------------MAIN----------------------------------------------------
int main(){
    // Variables
    srand(time(NULL));
    Usuario user;

    string tempName;

    // Ventana
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // Iniciar pantallas
    Pantalla pantalla_actual = INICIO;
    Cargas img; // Fondo
    img = CargarContenido(pantalla_actual, img);

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        BeginDrawing();
        switch(pantalla_actual)
        {
            case INICIO:
            {
                DibujarInicio(img);
                if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    // Primero descargar la pantalla actual
                    DescargarContenido(pantalla_actual, img); //En vez de tener que enviar una cadena podemos solamente enviar la pantalla
                    // Actualizamos la variable que representa la pantalla
                    pantalla_actual = CREAR_DUENO;
                    // Actualizamos la textura
                    img = CargarContenido(pantalla_actual, img);
                }
                
                break;
            }
            case CREAR_DUENO:
            {
                tempName = DibujarCrearPerfil(img,ANCHO,ALTO);
                user.DefineName(tempName);
                if(tempName != " "){
                    user.GetName();
                    DescargarContenido(pantalla_actual, img);
                    pantalla_actual = MIS_MASCOTAS;
                    img = CargarContenido(pantalla_actual, img);
                }
                break;
            }
            case MIS_MASCOTAS:
            {
                DibujarMisMascotas(img);
                DescargarContenido(pantalla_actual, img);
                pantalla_actual = CREAR_MASCOTA;
                img = CargarContenido(pantalla_actual, img);
                break;
            }
            case CREAR_MASCOTA:
            {
                cout<<"ENTRO AQUI"<<endl;
                DibujarCrearMascota(img);
                if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    DescargarContenido(pantalla_actual, img);
                    pantalla_actual = CREAR_MASCOTA;
                    img = CargarContenido(pantalla_actual, img);
                }
                break;
            }
            break;
            default:
                break;
        }
        EndDrawing();
        // DibujarMenu(pantalla_actual, archivos);
    }

    // DESCARGAR CONTENIDO
    DescargarContenido(pantalla_actual, img);
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
            archivos.FondoInicio=LoadTexture("../assets/MisMascotas.png");
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
    //     WHITE);
    DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.0f,WHITE);
    
    return 0;
}

// DIBUJAR LA PANTALLA DE CREAR DUEÑO
int DibujarCrearDueno(Cargas archivos){
    // DrawTexturePro(
    //     archivos.FondoInicio,
    //     (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
    //     (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
    //     (Vector2){0, 0},
    //     0.0f,
    //     WHITE);
    DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.0f,WHITE);

    return 0;
}

string DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight){
    const int MaxCharacter=20;
    int CharacterCont=0;
    char name[MaxCharacter+1];
    string nombre;
    bool band= false;
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
        if (IsKeyPressed(KEY_ENTER)){
            band = true;
        }

        EndDrawing();
    } while (band == false);
    nombre = name;
    return nombre;
}

void DibujarMisMascotas(Cargas archivos){
    while (true)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.2f,WHITE);
        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            break;
        }
        EndDrawing();
    }
    
}

void DibujarCrearMascota(Cargas archivos){
    
    // DrawTexturePro(archivos.FondoInicio,
    //     (Rectangle){0, 0, (float)archivos.FondoInicio.width, (float)archivos.FondoInicio.height},
    //     (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
    //     (Vector2){0, 0},
    //     0.0f,
    // WHITE);
    DrawTextureEx(archivos.FondoInicio,archivos.Position,0.0f,1.0f,WHITE);
}

