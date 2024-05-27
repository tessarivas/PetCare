#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

#include "clases/Usuario.h"
#include "clases/Dog.h"
#include "clases/Cat.h"

#include "functions/Calendario.h"
#include "functions/Mascota.h"


using std::cout;
using std::endl;
using std::string;
using std::pair;

// DEFINICIONES
#define ANCHO 414
#define ALTO 896

//---------------------Escenarios------------------------------------------------
typedef enum Pantalla{
    INICIO = 0,
    CREAR_DUENO, 
    MIS_MASCOTAS,
    CREAR_MASCOTA,
    // Registrar
    REGISTRAR_PERRO,
    REGISTRAR_GATO,
    AVATAR_PERRO,
    MI_PERFIL,
    CALENDARIO,
} Pantalla;

/*
    La estructura de cargas esta en Images.h, y no hace falta incluirla aqui porque ya la estamos incluyendo en Mascota.h
    y al incluir mascota.h ya se incluyen las demas librerias papu
*/

//------------------Load And Unload Content----------------------------------------//
Cargas CargarContenido(Pantalla actual, Cargas archivos);
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

//---------------------------Inicio-----------------------------------------------//
int DibujarInicio(Cargas archivos);

pair<string, bool> DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight);

Pantalla MiPerfil(Cargas archivos,int screenWidth, int screenHeight, Dog perro);
//-------------------------MAIN----------------------------------------------------//
int main(){

    // Ventana
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // Iniciar pantallas
    Pantalla pantalla_actual = INICIO;
    Cargas fondo_actual;
    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);

    // Variables
    srand(time(NULL));
    // Usuario
    Usuario user; // Usuario actual
    string tempName; // Nombre para copiar y pegar en el constructor de user

    // Mascota
    Dog perro;
    Cat cat;
    
    /*1 = gato, 2 = perro*/
    int mascota_actual;

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        BeginDrawing();

        switch(pantalla_actual)
        {
            case INICIO:
            {
                int boton_click_inicio;
                boton_click_inicio = DibujarInicio(fondo_actual);
                if(IsKeyPressed(KEY_SPACE) || boton_click_inicio == 1){
                    DescargarContenido(INICIO, fondo_actual);
                    pantalla_actual = CREAR_DUENO;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                break;
            }
            case CREAR_DUENO:
            {
                auto [tempName, regresar] = DibujarCrearPerfil(fondo_actual, ANCHO, ALTO);
                if (regresar) {
                    // Si se debe regresar, limpiar contenido y volver a la pantalla de inicio
                    DescargarContenido(CREAR_DUENO, fondo_actual);
                    pantalla_actual = INICIO;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                } else {
                    user.DefineName(tempName);
                    if (tempName != " ") {
                        user.GetName();
                        DescargarContenido(CREAR_DUENO, fondo_actual);
                        pantalla_actual = MIS_MASCOTAS;
                        fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                    }
                }
                break;
            }
            case MIS_MASCOTAS:
            {
                DibujarMisMascotas(fondo_actual,ANCHO,ALTO);
                DescargarContenido(MIS_MASCOTAS, fondo_actual);
                pantalla_actual = CREAR_MASCOTA;
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case CREAR_MASCOTA:
            {
                mascota_actual = DibujarCrearMascota(fondo_actual,ANCHO,ALTO);
                DescargarContenido(CREAR_MASCOTA,fondo_actual);
                if(mascota_actual == 1){
                    // Flata hacer una escena para los gatos
                    pantalla_actual = REGISTRAR_PERRO;
                }
                else if(mascota_actual == 2){
                    pantalla_actual = REGISTRAR_PERRO;
                } else{
                    pantalla_actual = MIS_MASCOTAS;;
                }
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case REGISTRAR_PERRO:
            {
                perro = RegistrarDog(fondo_actual,ANCHO,ALTO);
                // Nueva escena
                pantalla_actual=AVATAR_PERRO;
                // Descargar y cargar
                UnloadTexture(fondo_actual.FondoRegPerro);
                // Cargamos la pantalla siguiente
                fondo_actual.Background=LoadTexture("../assets/PetCare_MiPerroAvatar.png");
                break;
            }
            case AVATAR_PERRO:
            {
                // cargamos la textura que selecciono el usuario
                perro.Avatar = SeleccionarAvatarPerro(fondo_actual,ANCHO,ALTO);
                
                pantalla_actual=MI_PERFIL;

                UnloadTexture(fondo_actual.Background);
                fondo_actual.Background=LoadTexture("../assets/PetCare_MiPerfil.png");
                break;
            }
            case MI_PERFIL:
            {   
                pantalla_actual= MiPerfil(fondo_actual,ANCHO,ALTO,perro);
                UnloadTexture(fondo_actual.Background);
                break;
            }
            case CALENDARIO:
            {
                DibujarCalendario(perro,ANCHO,ALTO);
                break;
            }
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
            archivos.BotonListo = LoadTexture("../assets/PetCare_BotonListo.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.Avatar1 = LoadTexture("../assets/PetCare_Avatares/1.png");
            archivos.Avatar2 = LoadTexture("../assets/PetCare_Avatares/2.png");
            archivos.Avatar3 = LoadTexture("../assets/PetCare_Avatares/3.png");
            archivos.Avatar4 = LoadTexture("../assets/PetCare_Avatares/4.png");
            archivos.Avatar5 = LoadTexture("../assets/PetCare_Avatares/5.png");
            archivos.Avatar6 = LoadTexture("../assets/PetCare_Avatares/6.png");
            archivos.Fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");
            break;
        }
        case MIS_MASCOTAS:
        {
            archivos.FondoMisMascotas = LoadTexture("../assets/PetCare_MisMascotas.png");
            archivos.BotonAnadir = LoadTexture("../assets/PetCare_BotonAnadir.png");
            break;
        }
        case CREAR_MASCOTA:
        {
            archivos.FondoAnadirMascotas = LoadTexture("../assets/PetCare_AnadirMascotas.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonPerro = LoadTexture("../assets/PetCare_BotonPerro.png");
            archivos.BotonGato = LoadTexture("../assets/PetCare_BotonGato.png");
            break;
        }
        case REGISTRAR_PERRO:
        {
            archivos.FondoRegPerro = LoadTexture("../assets/PetCare_MiPerroDatos.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonAdelante = LoadTexture("../assets/PetCare_BotonAdelante.png");
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
        UnloadTexture(archivos.BotonListo);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.Avatar1);
        UnloadTexture(archivos.Avatar2);
        UnloadTexture(archivos.Avatar3);
        UnloadTexture(archivos.Avatar4);
        UnloadTexture(archivos.Avatar5);
        UnloadTexture(archivos.Avatar6);
        UnloadFont(archivos.Fuente);
    }
    if(pantalla_actual == MIS_MASCOTAS){
        UnloadTexture(archivos.FondoMisMascotas);
        UnloadTexture(archivos.BotonAnadir);
    }
    if(pantalla_actual == CREAR_MASCOTA){
        UnloadTexture(archivos.FondoAnadirMascotas);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonPerro);
        UnloadTexture(archivos.BotonGato);
    }
    if(pantalla_actual == REGISTRAR_PERRO){
        UnloadTexture(archivos.FondoRegPerro);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonAdelante);
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

// ------------- Registrar Perfil--------------- //
pair<string, bool> DibujarCrearPerfil(Cargas archivos,int screenWidth,int screenHeight){
    const int MaxCharacter=20;
    int CharacterCont=0;
    
    char name[MaxCharacter+1] = "";
    string nombre;
    
    bool regresar = false; // Para boton atras
    bool band = false; // Para boton listo
    
    Vector2 Mouse; // Posicion actual de mouse
    Vector2 LastClick; // Posicion del ultimo click

    int tamano_fondo = GetScreenWidth();
    // Color color_fondo_texto = { 251, 247, 235, 255 }; //Color de fondo

    // Boton atras
    Rectangle atras;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;
    atras.y = 20;
    atras.x = 20;

    // Boton listo
    Rectangle listo;
    listo.width=screenWidth*0.55;
    listo.height=screenHeight*0.1;
    listo.y=screenHeight*0.75;
    listo.x=(screenWidth/2) - (listo.width/2);

    // Cuadro de texto de nombre
    Rectangle c_name;
    c_name.x=(tamano_fondo - 320 )/2;
    c_name.y=320.0f;
    c_name.width=320.0f;
    c_name.height=70.0f;

    // Cuadro de avatares
    Rectangle c_avatares;
    c_avatares.x=(tamano_fondo - 320 )/2;
    c_avatares.y=430;
    c_avatares.width=320;
    c_avatares.height=225;

    // HitBox de avatares
    Rectangle av1;
    av1.x=screenWidth * 0.13;
    av1.y=screenHeight * 0.49;
    av1.width = screenWidth * 0.2;
    av1.height = screenHeight * 0.1;

    Rectangle av2;
    av2.x=screenWidth * 0.40;
    av2.y=screenHeight * 0.49;
    av2.width = screenWidth * 0.2;
    av2.height = screenHeight * 0.1;

    Rectangle av3;
    av3.x=screenWidth * 0.67;
    av3.y=screenHeight * 0.49;
    av3.width = screenWidth * 0.2;
    av3.height = screenHeight * 0.1;

    Rectangle av4;
    av4.x=screenWidth * 0.13;
    av4.y=screenHeight * 0.62;
    av4.width = screenWidth * 0.2;
    av4.height = screenHeight * 0.1;

    Rectangle av5;
    av5.x=screenWidth * 0.40;
    av5.y=screenHeight * 0.62;
    av5.width = screenWidth * 0.2;
    av5.height = screenHeight * 0.1;

    Rectangle av6;
    av6.x=screenWidth * 0.67;
    av6.y=screenHeight * 0.62;
    av6.width = screenWidth * 0.2;
    av6.height = screenHeight * 0.1;
    
    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            LastClick = Mouse;
        }

        //Fondo
        DrawTextureEx(archivos.FondoCrearDueno,archivos.Position,0.0f,1.0f,WHITE);

        //Rectangulo de nombre
        DrawRectangleRec(c_name, YELLOW);

        //Cuadro de texto
        Vector2 posicion_texto = {55, 325};
        DrawTextEx(archivos.Fuente, name, posicion_texto, 30, 2, BLACK);

        //Rectangulo de avatares
        DrawRectangleRec(c_avatares, YELLOW);
        // float rectX = (tamano_fondo - 320.0f) / 2;
        // DrawRectangle(rectX, 320.0f, 320.0f, 70.0f, color_fondo_texto); // RECTANGULO NOMBRE
        // DrawRectangle(rectX, 430.0f, 320.0f, 300.0f, color_fondo_texto); // RECTANGULO AVATAR

        int key = GetCharPressed(); // Tecla presionada

        // Checar si dio click en el cuadro de nombre
        if(CheckCollisionPointRec(LastClick, c_name)){
            // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada
            while (key > 0){
                if ((key >= 32) && (key <= 125) && (CharacterCont <MaxCharacter)){ // Solo caracteres entre el 32 y 125
                    name[CharacterCont] = (char)key; // Transformar el caracter de codigo asci a caracter
                    name[CharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                    CharacterCont++; // Aumentamos el contador de caracteres
                }
                key = GetCharPressed();  // revisamos si hay nuevos caracteres en cola
            }

            if (IsKeyPressed(KEY_BACKSPACE)){
                if (CharacterCont <= 0){
                    // Si la cadena esta vacia no hara nada
                } else{
                    name[CharacterCont] = '\0'; //Al ultimo que antes era una letra la sustituimos por el caracter nulo
                    CharacterCont--; //Si no esta vacia eliminara un espacio     
                }
            }
        }

        // HitBox de avatares
        DrawTextureEx(archivos.Avatar1, { av1.x, av1.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(archivos.Avatar2, { av2.x, av2.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(archivos.Avatar3, { av3.x, av3.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(archivos.Avatar4, { av4.x, av4.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(archivos.Avatar5, { av5.x, av5.y }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(archivos.Avatar6, { av6.x, av6.y }, 0.0f, 1.0f, WHITE);

        // Boton atras
        DrawTexture(archivos.BotonAtras, atras.x, atras.y, WHITE);

        // Verificar si se presiono atras
        if(CheckCollisionPointRec(LastClick, atras)){
            regresar = true;
            break;
        }

        // Boton listo
        DrawTexture(archivos.BotonListo, listo.x, listo.y, WHITE);

        // Verificar si se presiono listo
        if(CheckCollisionPointRec(LastClick, listo)){
            band = true;
        }

        EndDrawing();
        } while(band == false);

    nombre = name;
    return make_pair(nombre, regresar);
}

// ---------------- Mi perfil ---------------------//
Pantalla MiPerfil(Cargas archivos,int screenWidth, int screenHeight, Dog perro){
    /*
        Habria que, o adaptar la funcion de mi perfil para que acepte tanto perros y gatos, 
        o hacer una clase animal que contenga a los 2 . _  .
    */
    bool select=false;

    // Posicion del avatar
    Vector2 AvatarPos;
    AvatarPos.x=screenWidth*0.2;
    AvatarPos.y=screenHeight*0.91;

    Rectangle info;
    info.x=screenWidth * 0.2;
    info.y=screenHeight * 0.27;
    info.width = screenWidth * 0.6;
    info.height = screenHeight * 0.1;

    Rectangle cartilla;
    cartilla.x=screenWidth *0.2;
    cartilla.y=screenHeight * 0.43;
    cartilla.width = screenWidth * 0.6;
    cartilla.height=screenHeight * 0.18;
    
    Rectangle calendario;
    calendario.x=screenWidth *0.2;
    calendario.y=screenHeight * 0.66;
    calendario.width = screenWidth * 0.6;
    calendario.height=screenHeight * 0.18;


    // lo transformamos a cadena
    const char * mascota=perro.Nombre.c_str();


    while(select==false)
    {
        BeginDrawing();
            // Fondo
            DrawTextureEx(archivos.Background, archivos.Position,0.0f,1.0f,WHITE);
            
            DrawRectangleRec(info,RED);
            DrawRectangleRec(cartilla,BLUE);
            DrawRectangleRec(calendario,YELLOW);
            
            
            // avatar de perro
            DrawTextureEx(perro.Avatar,AvatarPos,0.0f,0.8f,WHITE);
            // Nombre del perro
            DrawText(mascota,screenWidth * 0.4, screenHeight * 0.93,40,BLACK);

        EndDrawing();
    }
}


