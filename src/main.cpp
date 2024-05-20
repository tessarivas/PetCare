#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cmath>

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
    CREAR_DUENO, 
    MIS_MASCOTAS,
    CREAR_MASCOTA,
} Pantalla;

//----------------------Images----------------------------------------------------
typedef struct Cargas{
    // INICIO
    Texture2D FondoInicio;
    Texture2D BotonEntrar;
    // CREAR DUEÑO
    Texture2D FondoCrearDueno;
    // MIS MASCOTAS
    Texture2D FondoMisMascotas;
    // AÑADIR MASCOTAS
    Texture2D FondoAnadirMascotas;
    Vector2 Position = { 0.0f, 0.0f };
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
    Cargas fondo_actual;
    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
    Cargas archivos;

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        BeginDrawing();
        int boton_click_inicio = DibujarInicio(archivos); // Solo cuando se de click al boton y no en cualquier parte de la pantalla

        switch(pantalla_actual)
        {
            case INICIO:
            {
                DibujarInicio(fondo_actual);
                if(IsKeyPressed(KEY_SPACE) || boton_click_inicio == 1){
                    DescargarContenido(INICIO, fondo_actual);
                    pantalla_actual = CREAR_DUENO;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                break;
            }
            case CREAR_DUENO:
            {
                tempName = DibujarCrearPerfil(fondo_actual,ANCHO,ALTO);
                user.DefineName(tempName);
                if(tempName != " "){
                    user.GetName();
                    DescargarContenido(CREAR_DUENO, fondo_actual);
                    pantalla_actual = MIS_MASCOTAS;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                break;
            }
            case MIS_MASCOTAS:
            {
                DibujarMisMascotas(fondo_actual);
                DescargarContenido(MIS_MASCOTAS, fondo_actual);
                pantalla_actual = CREAR_MASCOTA;
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case CREAR_MASCOTA:
            {
                cout<<"ENTRO AQUI"<<endl;
                DibujarCrearMascota(fondo_actual);
                if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    pantalla_actual = CREAR_MASCOTA;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                break;
            }
            break;
            default:
                break;
        }
        EndDrawing();
    }

    // DESCARGAR CONTENIDO
    DescargarContenido(pantalla_actual, fondo_actual);
    UnloadImage(icono);

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
            archivos.BotonEntrar = LoadTexture("../assets/PetCare_BotonEntrar.png");
            break;
        }
        case CREAR_DUENO:
        {
            archivos.FondoCrearDueno = LoadTexture("../assets/PetCare_CrearDueno.png");
            break;
        }
        case MIS_MASCOTAS:
        {
            archivos.FondoMisMascotas=LoadTexture("../assets/PetCare_MisMascotas.png");
            break;
        }
        case CREAR_MASCOTA:
        {
            archivos.FondoAnadirMascotas=LoadTexture("../assets/PetCare_AnadirMascota.png");
            break;
        }
        default:
        break;
    }
    return archivos;
}

// DESCARGAR TODAS LAS IMAGENES, AUDIO, FONTS, ETC...
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos){
    if(pantalla_actual == INICIO){
        UnloadTexture(archivos.FondoInicio);
        UnloadTexture(archivos.BotonEntrar);
    }
    if(pantalla_actual == CREAR_DUENO){
        UnloadTexture(archivos.FondoCrearDueno);
    }
    if(pantalla_actual == MIS_MASCOTAS){
        UnloadTexture(archivos.FondoMisMascotas);
    }
    if(pantalla_actual == CREAR_MASCOTA){
        UnloadTexture(archivos.FondoAnadirMascotas);
    }
}

// DIBUJAR LA PANTALLA DE INICIO CON LA QUE ENTRARA
int DibujarInicio(Cargas archivos) {
    // FONDO DE INICIO
    DrawTextureEx(archivos.FondoInicio, archivos.Position, 0.0f, 1.0f, WHITE);

    // ------------------- BOTON "ENTRAR" -------------------
    // Tamaño del boton
    float boton_entrar_width = static_cast<float>(archivos.BotonEntrar.width);
    float boton_entrar_height = static_cast<float>(archivos.BotonEntrar.height);
    // Posición del boton centrado en la parte inferior de la pantalla
    float boton_entrar_x = (GetScreenWidth() - boton_entrar_width) / 2;
    float boton_entrar_y = GetScreenHeight() - boton_entrar_height - 30; 
    // Dibujar el boton
    DrawTexture(archivos.BotonEntrar, boton_entrar_x, boton_entrar_y, WHITE);
    // Verificar si se presiona el boton
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && 
        CheckCollisionPointRec(GetMousePosition(), { boton_entrar_x, boton_entrar_y, boton_entrar_width, boton_entrar_height })) {
        return 1;
    }

    return 0;
}

// DIBUJAR LA PANTALLA DE CREAR DUEÑO
int DibujarCrearDueno(Cargas archivos){

    DrawTextureEx(archivos.FondoCrearDueno,archivos.Position,0.0f,1.0f,WHITE);

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
        DrawTextureEx(archivos.FondoCrearDueno,archivos.Position,0.0f,1.0f,WHITE);
        ClearBackground(WHITE);

        int tamano_fondo = GetScreenWidth();
        float rectX = (tamano_fondo - 320.0f) / 2;
        Color color_fondo_texto = { 251, 247, 235, 255 };
        DrawRectangle(rectX, 320.0f, 320.0f, 70.0f, color_fondo_texto); // RECTANGULO NOMBRE
        DrawRectangle(rectX, 430.0f, 320.0f, 300.0f, color_fondo_texto); // RECTANGULO AVATAR
        DrawText(name,55,325,30,BLACK);
        
        int key = GetCharPressed();

        // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (CharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
            {
                name[CharacterCont] = (char)key; //transformar el caracter de codigo asci a caracter
                name[CharacterCont+1] = '\0'; //Agregar caracter nulo al final de la cadena
                CharacterCont++; //Aumentamso el contador de caracteres
            }

            key = GetCharPressed();  // revisamos si hay nuevos caracteres en cola
        }

        if (IsKeyPressed(KEY_BACKSPACE)) //Borrar
        {
            if (CharacterCont < 0){
                // Si la cadena esta vacia no hara nada
            }
            else
            {
                CharacterCont--; //Si no esta vacia eliminara un espacio     
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
        DrawTextureEx(archivos.FondoMisMascotas,archivos.Position,0.0f,1.0f,WHITE);
        if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            break;
        }
        EndDrawing();
    }
}

void DibujarCrearMascota(Cargas archivos){
    DrawTextureEx(archivos.FondoMisMascotas,archivos.Position,0.0f,1.0f,WHITE);
}

