#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 
// comentario
#include "clases/Usuario.h"

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
    AVATAR_GATO,
    MI_PERFIL,
    CALENDARIO,
} Pantalla;

/*
    La estructura de cargas esta en Images.h, y no hace falta incluirla aqui porque ya la estamos incluyendo en Mascota.h
    y al incluir mascota.h ya se incluyen las demas librerias papu
*/

/*
    ---------------Nos hace falta---------------
    Remplazar algunos fondos
    
    Avatares de perros y gatos
    El boton de regresar al registrar mascota
    
    Cartilla medica

    Remplazar fondo del calendario
    Poner una condicion para los meses y anio bisiesto
    Hacer que el usuario guarde el dia, el titulo, y el asunto que guarde en el calendario
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
    Pantalla pantalla_actual = CREAR_MASCOTA;
    Cargas fondo_actual;
    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);

    // Eventos
    Evento *event=nullptr;

    // Variables
    srand(time(NULL));
    // Usuario
    Usuario user; // Usuario actual
    string tempName; // Nombre para copiar y pegar en el constructor de user

    // Mascota
    Dog perro;
    
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
                    pantalla_actual = REGISTRAR_GATO;
                }
                else if(mascota_actual == 2){
                    pantalla_actual = REGISTRAR_PERRO;
                } else{
                    pantalla_actual = MIS_MASCOTAS;;
                }
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case REGISTRAR_GATO:
            {
                perro = RegistrarDog(fondo_actual,ANCHO,ALTO);
                // Nueva escena
                // Seria la de los gatos
                pantalla_actual=AVATAR_GATO;
                // Descargar y cargar
                UnloadTexture(fondo_actual.FondoRegPerro);
                // Cargamos la pantalla siguiente
                fondo_actual.Background=LoadTexture("../assets/temp/MiGatoAvatares.png");
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
            case AVATAR_GATO:
            {
                // cargamos la textura que selecciono el usuario
                perro.Avatar = SeleccionarAvatarPerro(fondo_actual,ANCHO,ALTO);
                
                pantalla_actual=MI_PERFIL;

                UnloadTexture(fondo_actual.Background);
                break;
            }
            case MI_PERFIL:
            {   
                fondo_actual.Background=LoadTexture("../assets/PetCare_MiPerfil.png");
                pantalla_actual= MiPerfil(fondo_actual,ANCHO,ALTO,perro);
                UnloadTexture(fondo_actual.Background);
                break;
            }
            case CALENDARIO:
            {
                // Evento temporal
                Evento *tempEvent=nullptr;

                // Carga y descarga en la propia funcion
                tempEvent = DibujarCalendario(ANCHO,ALTO);

                if(tempEvent !=nullptr){
                    // Escribio eventos
                    // Dia temporal para transferir el dia a la estructura
                    int tempDia=tempEvent->day;
                    // Dia temporal para transferir el mes a la estructura
                    int tempMonth=tempEvent->month;
                    
                    char tempTitle[20];
                    strcpy(tempTitle,tempEvent->title);
                    
                    char tempDesc[50];
                    strcpy(tempDesc,tempEvent->description);

                    // Agregar el evento nuevo a la lista de eventos    
                    addEvent(&event,tempDia,tempMonth,tempTitle,tempDesc);
                    
                    pri(event);
                }
                else{
                    // No escribio ningun evento
                }
                    DibujarEventos(event,ANCHO,ALTO);
                
                pantalla_actual=MI_PERFIL;
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

    free(event);
    
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
            archivos.fuente=LoadFont("../assets/Fuentes/TangoSans.ttf");
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
        case REGISTRAR_GATO:
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
pair<string, bool> DibujarCrearPerfil(Cargas archivos,int screenWidth,int screenHeight)
{
    const int MaxCharacter=20;

    int CharacterCont=0;
    int tamano_fondo = GetScreenWidth(); // Obtener el tmaño del fondo
    int avatarSeleccionado = -1; // Avatar seleccionado

    char name[MaxCharacter+1] = "";

    bool regresar = false; // Para boton atras
    bool band = false; // Para boton listo

    string nombre;
    
    Vector2 Mouse; // Posicion actual de mouse
    Vector2 LastClick; // Posicion del ultimo click

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
    Rectangle Avatar[6];

    Avatar[0].x=screenWidth * 0.15;
    Avatar[0].y=screenHeight * 0.50;
    Avatar[0].width = screenWidth * 0.2;
    Avatar[0].height = screenHeight * 0.1;

    Avatar[1].x=screenWidth * 0.40;
    Avatar[1].y=screenHeight * 0.50;
    Avatar[1].width = screenWidth * 0.2;
    Avatar[1].height = screenHeight * 0.1;

    Avatar[2].x=screenWidth * 0.66;
    Avatar[2].y=screenHeight * 0.50;
    Avatar[2].width = screenWidth * 0.2;
    Avatar[2].height = screenHeight * 0.1;

    Avatar[3].x=screenWidth * 0.15;
    Avatar[3].y=screenHeight * 0.62;
    Avatar[3].width = screenWidth * 0.2;
    Avatar[3].height = screenHeight * 0.1;

    Avatar[4].x=screenWidth * 0.40;
    Avatar[4].y=screenHeight * 0.62;
    Avatar[4].width = screenWidth * 0.2;
    Avatar[4].height = screenHeight * 0.1;

    Avatar[5].x=screenWidth * 0.66;
    Avatar[5].y=screenHeight * 0.62;
    Avatar[5].width = screenWidth * 0.2;
    Avatar[5].height = screenHeight * 0.1;

    // Textura de cada avatar
    Texture2D avataresTexturas[6] = { archivos.Avatar1, archivos.Avatar2, archivos.Avatar3, archivos.Avatar4, archivos.Avatar5, archivos.Avatar6 };
    
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
        DrawRectangleRec(c_name, archivos.Bloque1);

        //Cuadro de texto
        Vector2 posicion_texto = {55, 325};
        DrawTextEx(archivos.fuente, name, posicion_texto, 30, 2, BLACK);

        //Rectangulo de avatares
        DrawRectangleRec(c_avatares, YELLOW);

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

        // Verificar si se hizo clic en algun avatar
        for (int i = 0; i < 6; i++) {
            if (CheckCollisionPointRec(LastClick, Avatar[i])){
                avatarSeleccionado = i;
            }
        }

        // Dibujar los avatares y bordes si están seleccionados
        for (int i = 0; i < 6; i++){
            if (avatarSeleccionado == i){
                // Dibujar borde de color si esta seleccionado
                DrawRectangleLinesEx(Avatar[i], 8, GREEN);
            }
            DrawTextureEx(avataresTexturas[i], { Avatar[i].x, Avatar[i].y }, 0.0f, 1.0f, WHITE);
        }

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
    // Posicion del texto de la mascota
    Vector2 mascotaPos;
    mascotaPos.x=screenWidth * 0.4;
    mascotaPos.y=screenHeight * 0.92;

    Vector2 Mouse;
    Vector2 Click;

    while(select==false)
    {
        BeginDrawing();
            Mouse=GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Click=Mouse;
            }
            
            // Fondo
            DrawTextureEx(archivos.Background, archivos.Position,0.0f,1.0f,WHITE);
            
            DrawRectangleRec(info,RED);

            DrawRectangleRec(cartilla,BLUE);

            DrawRectangleRec(calendario,YELLOW);
            
            if(CheckCollisionPointRec(Click,calendario)){
                return CALENDARIO;
            }

            // avatar de perro
            DrawTextureEx(perro.Avatar,AvatarPos,0.0f,0.8f,WHITE);
            // Nombre del perro
            DrawTextEx(archivos.fuente,mascota,mascotaPos,40.0f,2.0f,BLACK);

        EndDrawing();
    }
    return CALENDARIO;
}