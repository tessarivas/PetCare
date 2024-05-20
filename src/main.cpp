#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cmath>

#include "classes/Usuario.h"
#include "classes/Dog.h"
#include "classes/Cat.h"

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
    // Registrar
    REGISTRAR_PERRO,
    REGISTRAR_GATO,
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
    // REGISTRAR PERRO
    Texture2D FondoRegPerro;
    // REGISTRAR GATO
    Texture2D FondoRegGato;

    Vector2 Position = { 0.0f, 0.0f };
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

//-----------------------Extra Functions-------------------------------------------//
void DibujarMisMascotas(Cargas archivos);
string DibujarCrearPerfil(Cargas archivos,int screenWeidth,int screenHeight);
int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight);
string CuadroDeTexto(Rectangle posicion,Color color);


//-------------------------MAIN----------------------------------------------------//
int main(){

    // Ventana
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);

    // Iniciar pantallas
    Pantalla pantalla_actual = REGISTRAR_PERRO;
    Cargas fondo_actual;
    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
    Cargas archivos;

    // Variables
    srand(time(NULL));
    // Usuario
    Usuario user; // Usuario actual
    string tempName; // Nombre para copiar y pegar en el constructor de user

    // Mascota
    Dog perro;
    Cat cat;
    
    /*0 = gato, 1 = perro*/
    int mascota_actual;

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        BeginDrawing();
        int boton_click_inicio; // Solo cuando se de click al boton y no en cualquier parte de la pantalla
        // Si esta bn pero la obtencion de la posicion del mouse deberia de estar en el ciclo, osea en el case inicio

        switch(pantalla_actual)
        {
            case INICIO:
            {
                boton_click_inicio= DibujarInicio(fondo_actual);
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
                mascota_actual = DibujarCrearMascota(fondo_actual,ANCHO,ALTO);
                DescargarContenido(CREAR_MASCOTA,fondo_actual);
                if(mascota_actual == 1){
                    pantalla_actual = REGISTRAR_PERRO;
                }
                else{
                    pantalla_actual = REGISTRAR_GATO;
                }
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case REGISTRAR_PERRO:
            {
                perro = RegistrarDog(fondo_actual,ANCHO,ALTO);
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
            break;
        }
        case MIS_MASCOTAS:
        {
            archivos.FondoMisMascotas=LoadTexture("../assets/PetCare_MisMascotas.png");
            break;
        }
        case CREAR_MASCOTA:
        {
            archivos.FondoAnadirMascotas=LoadTexture("../assets/PetCare_AnadirMascotas.png");
            break;
        }
        case REGISTRAR_PERRO:
        {
            archivos.FondoRegPerro = LoadTexture("../assets/Temp/RegistrarPerro.png");
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
    if(pantalla_actual == REGISTRAR_PERRO){
        UnloadTexture(archivos.FondoRegPerro);
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

string DibujarCrearPerfil(Cargas archivos,int screenWidth,int screenHeight){
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
            if (CharacterCont <= 0){
                // Si la cadena esta vacia no hara nada
            }
            else
            {
                name[CharacterCont] = '\0'; //Al ultimo que antes era una letra la sustituimos por el caracter nulo
                CharacterCont--; //Si no esta vacia eliminara un espacio     
            }
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
            DrawTextureEx(archivos.FondoMisMascotas,archivos.Position,0.0f,1.0f,WHITE);
            
            if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                break;
            }
        EndDrawing();
    }
}

int DibujarCrearMascota(Cargas archivos, int screenWidth, int screenHeight){
    //--------------Botones----------------//
    // Boton de gato
    Rectangle Cat;
    //Posicion
    Cat.x = screenWidth * 0.1; // El 20% de la pantalla
    Cat.y = screenHeight * 0.36;
    // Largo y ancho
    Cat.width= screenWidth * 0.79;
    Cat.height = 120;
    
    // Boton de perro
    Rectangle Dog;
    //Posicion
    Dog.x = screenWidth * 0.1; // El 20% de la pantalla
    Dog.y = screenHeight * 0.56; // un 20% mas abajo
    // Largo y ancho
    Dog.width= screenWidth * 0.79;
    Dog.height = 120;

    //----------Otras variables--------------//
    //Posicion actual del mouse
    Vector2 Mouse = {0.0f,0.0f};

    // Banderas
    // 0 = gato, 1 = perro
    int selection = 0;

    bool ciclo = true;

    //  Puedes usar la posicion del rectangulo para poner la imagen de los botones
    while (ciclo == true){
        BeginDrawing();
            //Fondo
            Mouse = GetMousePosition();
            DrawTextureEx(archivos.FondoAnadirMascotas,archivos.Position,0.0f,1.0f,WHITE);
            
            //Botones Posicion, Para no batallar con las imagenes podemos hacerlos invisibles y solo sobreponer las imagenes 
            DrawRectangleRec(Cat,RED);
            DrawRectangleRec(Dog,BLUE);

            // Comparar las posiciones del mouse con un rectangulo
            if(CheckCollisionPointRec(Mouse,Cat)){
                //Se encuentra encima del rectangulo
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    //Hace click
                    selection = 0;
                    ciclo = false;
                }
            }
            else{
                if(CheckCollisionPointRec(Mouse,Dog)){
                    //Se encuentra encima del rectangulo
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        //Hace click
                        selection = 1;
                        ciclo = false;
                    }
                }
            }
        EndDrawing();
    }
    return selection;
}

//--------------Registros de mascotas----------------//

Dog RegistrarDog(Cargas archivos, int screenWidth,int screenHeight){
    Dog temp;
    bool finish = false;
    //Cuadro de nombre
    Rectangle c_nombre;
    c_nombre.x=screenWidth * 0.1; // 10% de espacio entre el borde de la izquierda
    c_nombre.y=screenHeight * 0.3; // 30% de espacio entre el borde de arriba
    c_nombre.width = screenWidth * 0.78; // 78% de tamanio de la pantalla medira el cuadro de ancho
    c_nombre.height = 40; // 40px medira el cuadro
    
    //Cuado de raza
    Rectangle c_raza;
    c_raza.x=screenWidth * 0.1;
    c_raza.y=screenHeight * 0.4;
    c_raza.width = screenWidth * 0.78;
    c_raza.height = 40;
    
    //Cuadro de Fecha de nacimineto
    Rectangle c_nacimineto;
    c_nacimineto.x=screenWidth * 0.1;
    c_nacimineto.y=screenHeight * 0.5;
    c_nacimineto.width = screenWidth * 0.78;
    c_nacimineto.height = 40;
    
    //Cuadro de peso
    Rectangle c_peso;
    c_peso.x=screenWidth * 0.1;
    c_peso.y=screenHeight * 0.6;
    c_peso.width = screenWidth * 0.78;
    c_peso.height = 40;
    
    //Cuadro de padecimientos
    Rectangle c_padecimientos;
    c_padecimientos.x=screenWidth * 0.1;
    c_padecimientos.y=screenHeight * 0.7;
    c_padecimientos.width = screenWidth * 0.78;
    c_padecimientos.height = 40;

    string temp_name;

    Vector2 Mouse;
    Vector2 lastClick;

    // Maybe y los cuadros no esten centrados ahorita donde deberian de estar, pero eso se actualiza facil cuando pongamos el fondo original ;b
    while( finish == false){
        BeginDrawing();
        {
            // Maximo de caracteres
            const int MaxCharacter=20;
            // Cadena que almacenara caracter por caracter, +1 por el caracter nulo
            char name[MaxCharacter+1];
            char raza[MaxCharacter+1];
            
            char dia[MaxCharacter+1];
            char mes[MaxCharacter+1];
            char anio[MaxCharacter+1];
            
            //Contador de caracteres actuales
            int CharacterCont=0;
            
            // Bandera de ciclo
            bool band= false; 
            do
            {
                BeginDrawing();
                Mouse = GetMousePosition();
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    lastClick = Mouse;
                }

                // Fondo
                DrawTextureEx(archivos.FondoRegPerro,archivos.Position,0.0f,1.3f,WHITE);
                
                // Dibujar cuadro de texto
                DrawRectangleRec(c_nombre,RED);
                // Dibujar texto acutal de nombre
                DrawText(name,c_nombre.x+10,c_nombre.y+10,15,BLACK);
                
                /*
                    Como son varios cuadros de texto creo que tendria que copiar y pegar varias veces el ciclo para escribir pero hacer una validacion
                    para saber en que cuadro de texto estara escribiendo, podria hacer que el mouse tenga que estar encima de donde lo requiera o
                    una forma de que se quede registrado la ultima posicion donde dio click, y compararla con los cuadros de texto, dependiendo la posicion
                    que haga la funcion de x o y cuadro o.O

                    a wilson la 2da si jalo jijiji
                */

                // Tecla presionada en codigo ascii
                if(CheckCollisionPointRec(lastClick,c_nombre)){
                    int key = GetCharPressed();

                    // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 125) && (CharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
                        {
                            name[CharacterCont] = (char)key; //transformar el caracter de codigo ascii a caracter
                            name[CharacterCont+1] = '\0'; //Agregar caracter nulo al final de la cadena
                            CharacterCont++; //Aumentamos el contador de caracteres
                        }

                        key = GetCharPressed();  // revisamos si hay nuevos caracteres en cola en el mismo frame
                    }

                    if (IsKeyPressed(KEY_BACKSPACE)) //Borrar
                    {
                        if (CharacterCont < 0){
                            // Si la cadena esta vacia no hara nada
                        }
                        else
                        {
                            CharacterCont--; //Si no esta vacia eliminara un espacio     
                            name[CharacterCont] = '\0'; //Al ultimo que antes era una letra la sustituimos por el caracter nulo
                        }
                    }
                    if (IsKeyPressed(KEY_ENTER)){
                        
                    }
                }
                

                DrawRectangleRec(c_raza,GRAY);
                DrawRectangleRec(c_nacimineto,GRAY);
                DrawRectangleRec(c_peso,GRAY);
                DrawRectangleRec(c_padecimientos,GRAY);
                EndDrawing();
            } while (band == false);
            temp_name = name;
        }
        EndDrawing();
    }
    return temp;
}

// Funcion para un cuadro de texto
string CuadroDeTexto(Rectangle posicion,Color color){
    // Maximo de caracteres
    const int MaxCharacter=20;
    // Cadena que almacenara caracter por caracter, +1 por el caracter nulo
    char name[MaxCharacter+1];
    
    //Contador de caracteres actuales
    int CharacterCont=0;
    // string que regresaremos para el nombre
    string nombre;
    
    // Bandera de ciclo
    bool band= false; 
    do
    {
        BeginDrawing();

        //Dibujar cuadro de texto
        DrawRectangleRec(posicion,color);
        
        //Dibujar texto acutal
        DrawText(name,posicion.x-10,posicion.y-10,30,BLACK);
        
        // Tecla presionada en codigo ascii
        int key = GetCharPressed();

        // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (CharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
            {
                name[CharacterCont] = (char)key; //transformar el caracter de codigo ascii a caracter
                name[CharacterCont+1] = '\0'; //Agregar caracter nulo al final de la cadena
                CharacterCont++; //Aumentamos el contador de caracteres
            }

            key = GetCharPressed();  // revisamos si hay nuevos caracteres en cola en el mismo frame
        }

        if (IsKeyPressed(KEY_BACKSPACE)) //Borrar
        {
            if (CharacterCont <= 0){
                // Si la cadena esta vacia no hara nada
            }
            else
            {
                name[CharacterCont] = '\0'; //Al ultimo que antes era una letra la sustituimos por el caracter nulo
                CharacterCont--; //Si no esta vacia eliminara un espacio     
            }
        }
        if (IsKeyPressed(KEY_ENTER)){
            band = true;
        }

        EndDrawing();
    } while (band == false);

    nombre = name;
    return nombre;
}
