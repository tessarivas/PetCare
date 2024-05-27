#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

#include "classes/Usuario.h"
#include "classes/Dog.h"
#include "classes/Cat.h"

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

//----------------------Images----------------------------------------------------
typedef struct Cargas{
    // INICIO
    Texture2D FondoInicio;
    Texture2D BotonEntrar;
    // CREAR DUEÑO
    Texture2D FondoCrearDueno;
    Texture2D BotonListo;
    Texture2D BotonAtras;
    Texture2D Avatar1;
    Texture2D Avatar2;
    Texture2D Avatar3;
    Texture2D Avatar4;
    Texture2D Avatar5;
    Texture2D Avatar6;
    // MIS MASCOTAS
    Texture2D FondoMisMascotas;
    Texture2D BotonAnadir;
    // AÑADIR MASCOTAS
    Texture2D FondoAnadirMascotas;
    Texture2D BotonPerro;
    Texture2D BotonGato;
    // REGISTRAR PERRO
    Texture2D FondoRegPerro;
    Texture2D BotonAdelante;
    // REGISTRAR GATO
    Texture2D FondoRegGato;
    // EXTRAS
    Texture2D Background;
    Vector2 Position = { 0.0f, 0.0f };
    Font Fuente;
} Cargas;

//------------------Load And Unload Content----------------------------------------//
Cargas CargarContenido(Pantalla actual, Cargas archivos);
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

//-----------------------Draw Screen-----------------------------------------------//
void DibujarMenu(Pantalla pantalla_actual, Cargas archivos);
int DibujarInicio(Cargas archivos);
int DibujarCrearDueno(Cargas archivos);

//-----------------------Registro de mascotas--------------------------------------//
Dog RegistrarDog(Cargas archivos, int screenWidth,int screenHeight);
Texture2D SeleccionarAvatarPerro(Cargas archivos,int screenWidth, int screenHeight);

//-----------------------Extra Functions-------------------------------------------//
void DibujarMisMascotas(Cargas archivos, int screenWidth, int screenHeight);
pair<string, bool> DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight);
int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight);

Pantalla MiPerfil(Cargas archivos,int screenWidth, int screenHeight, Dog perro);
void DibujarCalendario(Dog perro, int screenWidth, int screenHeight);

//-------------------------MAIN----------------------------------------------------//
int main(){

    // Ventana
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // Iniciar pantallas
    Pantalla pantalla_actual = CALENDARIO;
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

//--------------Registros de mascotas----------------//
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
}

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

// Calendario
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

    Rectangle descrEvent;
    descrEvent.x=screenWidth*0.1;
    descrEvent.y=screenHeight*0.69;
    descrEvent.width=screenWidth*0.8;
    descrEvent.height=screenHeight*0.19;

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

    bool daySelected = false;

    float wi=0.05;
    float hi=0.27;
    Rectangle test;
    test.x=screenWidth*0.05;
    test.y=screenHeight*0.27;
    test.width=screenWidth*0.12;
    test.height=screenHeight*0.06;

    Vector2 Dia;

    int DiaSeleccionado;

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

            // ------DIAS DE LA SEMANA-----------//
            
            
            // Evento-------------------------
            //titulo
            DrawRectangleRec(titleEvent,YELLOW);
            //Descripcion
            DrawRectangleRec(descrEvent,YELLOW);

            // Aqui el codigo de nuevo para agergar texto

            // Agregar evento------------------
            DrawRectangleRec(Agregar,RED);

            // Regresar
            DrawRectangleRec(Return,BLUE);
            
            wi=0.05;
            hi=0.27;
            test.x=screenWidth*0.05;
            test.y=screenHeight*0.27;
            

            // Esta funcion me costo musho alv y tan simple que esta
            for(int i=1;i<=32;i++)
            {   
                if(CheckCollisionPointRec(lastclick,test))
                {
                    daySelected=true;
                    Dia=lastclick;
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

                    if(CheckCollisionPointRec(Dia,test)){
                        DiaSeleccionado=i;
                        cout<<"DIA "<< DiaSeleccionado<<endl;
                    }
                    
                    wi=wi+0.13;
                }
            }


        EndDrawing();
    }

}


