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
using std::atoi;
using std::string;
using std::pair;
using std::make_pair;

// EN ESTA FUNCION SE RELACIONA LA LIBRERIA DE Citas.h
#include "../clases/Usuario.h"

// ---------------------------------------------------------------------------- //

int DibujarCartillaMedica(Cita *citas, int screenWidth, int screenHeight);

pair<string, bool> DibujarAgregarCita(Cita **citasAgendadas, int screenWidth, int screenHeight);



// ---------------------------------------------------------------------------- //

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
    AgregarCita.y = screenHeight * 0.73;
    AgregarCita.x = (screenWidth / 2) - (AgregarCita.width / 2) - 13;
    // BOTON REGRESAR
    Texture2D BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
    Rectangle Atras;
    Atras.width = screenWidth * 0.55;
    Atras.height = screenHeight * 0.1;
    Atras.y = 20;
    Atras.x = 20;
    // FUENTE DE LETRA
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

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
            return 2;// No se como retornar bien
        }

        int x = 40;
        int y = 270; // Posición inicial en Y para imprimir las citas
        Vector2 Posicion = {x, y};
        Vector2 Posicion2 = {x, y + 20};
        Vector2 Posicion3 = {x, y + 40};
        Vector2 Posicion4 = {x, y + 60};
        Cita* temp = citas;
        while (temp != nullptr) {
            DrawTextEx(fuente, temp->titulo.c_str(), Posicion, 25, 0, BLACK);
            DrawTextEx(fuente, temp->descripcion.c_str(), Posicion2, 25, 0, BLACK); 
            // Convertir la fecha a una cadena 
            std::string fecha = "Fecha: " + std::to_string(temp->dia) + "/" + std::to_string(temp->mes);
            DrawTextEx(fuente, fecha.c_str(), Posicion3, 25, 0, BLACK);
            std::string tipo = temp->esVacuna ? "Tipo: Vacuna" : "Tipo: Revision";
            DrawTextEx(fuente, tipo.c_str(), Posicion4, 25, 0, BLACK);
            temp = temp->siguiente;
            y += 100; // Ajustar la posición en Y para la siguiente cita
            Posicion.y = y;
            Posicion2.y = y + 20;
            Posicion3.y = y + 40;
            Posicion4.y = y + 60;
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
    bool boton = false; // Para saber si selecciono vacuna o revision
    const int MaxCaracter = 20;
    // int tamano_fondo = GetScreenWidth();

    int cuenta_titulo = 0;
    int cuenta_descripcion = 0;
    int cuenta_dia = 0;
    int cuenta_mes = 0;
    int cuenta_anio = 0;

    char titulo[MaxCaracter + 1] = "";
    char descripcion[MaxCaracter + 1] = "";
    char dia[MaxCaracter + 1] = "";
    char mes[MaxCaracter + 1] = "";
    char anio[MaxCaracter + 1] = "";

    string temp_titulo;
    string temp_descripcion;
    int temp_dia;
    int temp_mes;
    int temp_anio;

    // FONDO "AGREGAR_CITA"
    Texture2D FondoMiCartilla = LoadTexture("../assets/PetCare_AgregarCita.png");
    Vector2 Posicion = { 0.0f, 0.0f }; // Posicion
    // BOTON AÑADIR CITA
    Texture2D BotonAgregarCita = LoadTexture("../assets/PetCare_BotonAnadir.png");
    Rectangle Anadir;
    Anadir.width = screenWidth * 0.55;
    Anadir.height = screenHeight * 0.1;
    Anadir.y = screenHeight * 0.78;
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
    Titulo.x = screenWidth * 0.1;
    Titulo.y = screenHeight * 0.3;
    Titulo.width = 320.0f;
    Titulo.height = 50.0f;
    // CUADRO DE DESCRIPCION
    Rectangle Descripcion;
    Descripcion.x = screenWidth * 0.1;
    Descripcion.y = screenHeight * 0.4;
    Descripcion.width = 320.0f;
    Descripcion.height = 70.0f;
    // FECHA (Dia, Mes, Anio)
    Rectangle Dia;
    Rectangle Mes;
    Rectangle Anio;
    Dia.x=screenWidth * 0.1;
    Dia.y=screenHeight * 0.53;
    Dia.width= screenWidth * 0.25;
    Dia.height = 40;
    Mes.x=screenWidth * 0.36;
    Mes.y=screenHeight * 0.53;
    Mes.width= screenWidth * 0.26;
    Mes.height = 40;
    Anio.x=screenWidth * 0.63;
    Anio.y=screenHeight * 0.53;
    Anio.width= screenWidth * 0.25;
    Anio.height = 40;
    // BOTON VACUNA
    Texture2D BotonVacuna = LoadTexture("../assets/PetCare_BotonVacuna.png");
    Rectangle Vacuna;
    Vacuna.width = screenWidth * 0.55;
    Vacuna.height = screenHeight * 0.1;
    Vacuna.y = screenHeight * 0.65;
    Vacuna.x = (screenWidth / 2) - (Anadir.width / 2) - 52;
    Vector2 BotonVacunaPosicion = {Vacuna.x, Vacuna.y};
    // BOTON REVISION
    Texture2D BotonRevision = LoadTexture("../assets/PetCare_BotonRevision.png");
    Rectangle Revision;
    Revision.width = screenWidth * 0.55;
    Revision.height = screenHeight * 0.1;
    Revision.y = screenHeight * 0.65;
    Revision.x = (screenWidth / 2) - (Anadir.width / 2) + 117;
    Vector2 BotonRevisionPosicion = {Revision.x, Revision.y};

    // FUENTE DE LETRA
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // Mouse y click
    Vector2 Mouse;
    Vector2 Click;

    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Click = Mouse;
        }

        // FondoMiCartilla Y BOTONES
        DrawTextureEx(FondoMiCartilla, Posicion, 0.0f, 1.0f, WHITE);
        DrawTexture(BotonAgregarCita, Anadir.x, Anadir.y, WHITE);
        DrawTexture(BotonAtras, Atras.x, Atras.y, WHITE);
        DrawTextureEx(BotonVacuna, BotonVacunaPosicion, 0.0f, 0.7f, WHITE);
        DrawTextureEx(BotonRevision, BotonRevisionPosicion, 0.0f, 0.7f, WHITE);
        // RECTANGULO DEL NOMBRE
        DrawRectangleRec(Titulo, YELLOW);
        // CUADRO DE TEXTO
        Vector2 posicion_titulo = {55, 280};
        DrawTextEx(fuente, titulo, posicion_titulo, 30, 2, BLACK);
        // RECTANGULO DEL DESCRIPCION
        DrawRectangleRec(Descripcion, YELLOW);
        // CUADRO DE TEXTO
        Vector2 posicion_descripcion = {55, 380};
        DrawTextEx(fuente, descripcion, posicion_descripcion, 30, 2, BLACK);
        // FECHA (Dia, Mes, Anio)
        DrawRectangleRec(Dia, YELLOW);
        DrawRectangleRec(Mes, YELLOW);
        DrawRectangleRec(Anio, YELLOW);
        Vector2 posicion_dia = {60, 480};
        DrawTextEx(fuente, dia, posicion_dia, 30, 2, BLACK);
        Vector2 posicion_mes = {170, 480};
        DrawTextEx(fuente, mes, posicion_mes, 30, 2, BLACK);
        Vector2 posicion_anio = {280, 480};
        DrawTextEx(fuente, anio, posicion_anio, 30, 2, BLACK);

        int tecla = GetCharPressed(); // Tecla presionada

        // TITULO
        if(CheckCollisionPointRec(Click, Titulo)){
            // Manejar la entrada de texto para el título de la cita
            while (tecla > 0){
                if ((tecla >= 32) && (tecla <= 125) && (cuenta_titulo < MaxCaracter)){
                    titulo[cuenta_titulo] = (char)tecla;
                    titulo[cuenta_titulo + 1] = '\0';
                    cuenta_titulo++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (cuenta_titulo > 0){
                    titulo[--cuenta_titulo] = '\0';
                }
            }
        }

        // DESCRIPCION
        if(CheckCollisionPointRec(Click, Descripcion)){
            while (tecla > 0){
                if ((tecla >= 32) && (tecla <= 125) && (cuenta_descripcion < MaxCaracter)){
                    descripcion[cuenta_descripcion] = (char)tecla;
                    descripcion[cuenta_descripcion + 1] = '\0';
                    cuenta_descripcion++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (cuenta_descripcion > 0){
                    descripcion[--cuenta_descripcion] = '\0';
                }
            }
        }

        // DIA
        if(CheckCollisionPointRec(Click, Dia)){
            while(tecla > 0){
                if ((tecla >= 48) && (tecla <= 57) && (cuenta_dia < MaxCaracter)){
                    dia[cuenta_dia] = (char)tecla;
                    dia[cuenta_dia + 1] = '\0';
                    cuenta_dia++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (cuenta_dia > 0){
                    dia[--cuenta_dia] = '\0';
                }
            }
        }

        // MES
        if(CheckCollisionPointRec(Click, Mes)){
            while(tecla > 0){
                if ((tecla >= 48) && (tecla <= 57) && (cuenta_mes < MaxCaracter)){
                    mes[cuenta_mes] = (char)tecla;
                    mes[cuenta_mes + 1] = '\0';
                    cuenta_mes++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (cuenta_mes > 0){
                    mes[--cuenta_mes] = '\0';
                }
            }
        }

        // ANIO
        if(CheckCollisionPointRec(Click, Anio)){
            while(tecla > 0){
                if ((tecla >= 48) && (tecla <= 57) && (cuenta_anio < MaxCaracter)){
                    anio[cuenta_anio] = (char)tecla;
                    anio[cuenta_anio + 1] = '\0';
                    cuenta_anio++;
                }
                tecla = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (cuenta_anio > 0){
                    anio[--cuenta_anio] = '\0';
                }
            }
        }

        // Verificar si se presiono atras y regresar a la pantalla que dibuja MiCartillaMedica
        if(CheckCollisionPointRec(Click, Atras)){
            regresar = true;
            UnloadTexture(FondoMiCartilla);
            UnloadTexture(BotonAgregarCita);
            UnloadTexture(BotonAtras);
            UnloadTexture(BotonVacuna);
            UnloadTexture(BotonRevision);
            return make_pair("", true);
        }

        // Agregar la cita, al presionar se regresa a la pantalla de MiCartillaMedica
        if(CheckCollisionPointRec(Click, Anadir)){
            band = true;
            UnloadTexture(FondoMiCartilla);
            UnloadTexture(BotonAgregarCita);
            UnloadTexture(BotonAtras);
            UnloadTexture(BotonVacuna);
            UnloadTexture(BotonRevision);
        }

        if(CheckCollisionPointRec(Click, Vacuna)){
            boton = true;
        }

        if(CheckCollisionPointRec(Click, Revision)){
            boton = false;
        }

        EndDrawing();
    }while(!regresar && !band);

    if(band){
        temp_titulo = string(titulo);
        temp_descripcion = string(descripcion);
        temp_dia = atoi(dia);
        temp_mes = atoi(mes);
        temp_anio = atoi(anio);

        AgregarCita(citasAgendadas, temp_dia, temp_mes, temp_titulo, temp_descripcion, boton);

        cout << "Cita anadida correctamente:\n";
        cout << "Titulo: " << temp_titulo << endl;
        cout << "Descripcion: " << temp_descripcion << endl;
        cout << "Fecha: " << temp_dia << "/" << temp_mes << "/" << temp_anio << endl;
        cout << "Tipo: " << (boton ? "Vacuna" : "Revision") << endl;

        return make_pair("Cita añadida correctamente", false);
    }

     return make_pair("", false); // Si se regresó no se añadio ninguna cita
}

RegistrarAccionCita DibujarDatosMedicos(Dog perro,const char dueno[] ,int screenWidth,int screenHeight){
    int opcion = 0;

    RegistrarAccionCita result = CONTINUA;
    
    Color trans ={255,0,0,100};

    // FONDO
    Texture2D background = LoadTexture("../assets/PetCare_CartillaMedicaInfo.png");
    Texture2D BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
    Texture2D BotonCitas = LoadTexture("../assets/PetCare_BotonCitas.png");

    // FUENTE DE LETRA
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // NOMBRE
    Rectangle NombreC;
    {
        NombreC.x=screenWidth *0.17;
        NombreC.y=screenHeight *0.26;
        NombreC.width=screenWidth*0.72;
        NombreC.height=screenHeight*0.06;
    }
    // RAZA
    Rectangle RazaC;
    {
        RazaC.x=screenWidth *0.17;
        RazaC.y=screenHeight *0.36;
        RazaC.width=screenWidth*0.72;
        RazaC.height=screenHeight*0.06;
    }
    // FECHA (DIA/MES/AÑO)
    Rectangle DiaC;
    {
        DiaC.x=screenWidth *0.17;
        DiaC.y=screenHeight *0.47;
        DiaC.width=screenWidth*0.23;
        DiaC.height=screenHeight*0.06;
    }
    Rectangle MesC;
    {
        MesC.x=screenWidth *0.42;
        MesC.y=screenHeight *0.47;
        MesC.width=screenWidth*0.22;
        MesC.height=screenHeight*0.06;
    }
    Rectangle AnioC;
    {
        AnioC.x=screenWidth *0.66;
        AnioC.y=screenHeight *0.47;
        AnioC.width=screenWidth*0.23;
        AnioC.height=screenHeight*0.06;
    }
    // PESO
    Rectangle PesoC;
    {
        PesoC.x=screenWidth *0.17;
        PesoC.y=screenHeight *0.58;
        PesoC.width=screenWidth*0.23;
        PesoC.height=screenHeight*0.06;  
    }
    // NOMBRE DEL DUEÑO
    Rectangle DuenoC;
    {
        DuenoC.x=screenWidth *0.44;
        DuenoC.y=screenHeight *0.58;
        DuenoC.width=screenWidth*0.45;
        DuenoC.height=screenHeight*0.06;  
    }
    // PADECIMIENTOS
    Rectangle PadeC;
    {
        PadeC.x=screenWidth *0.17;
        PadeC.y=screenHeight *0.69;
        PadeC.width=screenWidth*0.72;
        PadeC.height=screenHeight*0.06;  
    }
    // BOTON ATRAS
    Rectangle atras;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;
    atras.y = 20;
    atras.x = 20;
    // BOTON CITAS
    Rectangle citas;
    citas.width = screenWidth * 0.55;
    citas.height = screenHeight * 0.1;
    citas.y = screenHeight * 0.77;
    citas.x = (screenWidth / 2) - (citas.width / 2);
    
    Vector2 Mouse;
    Vector2 click;

    while(opcion == 0)
    {
        Mouse = GetMousePosition();
        BeginDrawing();
            // Fondo
            DrawTexture(background,0,0,WHITE);

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                click = Mouse;
            }

            DrawTexture(BotonAtras, atras.x, atras.y, WHITE);
            if(CheckCollisionPointRec(click, atras)){
                result = ATRAS;
                break;
            }

            DrawTexture(BotonCitas, citas.x, citas.y, WHITE);
            if(CheckCollisionPointRec(click, citas))
            {
                result = ADELANTE;
                break;
            }

            Vector2 nombrePos = {NombreC.x, NombreC.y};
            Vector2 razaPos = {RazaC.x, RazaC.y};
            Vector2 diaPos = {DiaC.x, DiaC.y};
            Vector2 mesPos = {MesC.x, MesC.y};
            Vector2 anioPos = {AnioC.x, AnioC.y};
            Vector2 pesoPos = {PesoC.x, PesoC.y};
            Vector2 duenoPos = {DuenoC.x, DuenoC.y};
            Vector2 padecimientosPos = {PadeC.x, PadeC.y};

            DrawTextEx(fuente, perro.getName().c_str(), nombrePos, 20, 1, BLACK);
            DrawTextEx(fuente, perro.getRaza().c_str(), razaPos, 20, 1, BLACK);
            DrawTextEx(fuente, TextFormat("%02i", perro.getDia()), diaPos, 20, 1, BLACK);
            DrawTextEx(fuente, TextFormat("%02i", perro.getMonth()),mesPos , 20, 1, BLACK);
            DrawTextEx(fuente, TextFormat("%04i", perro.getYear()), anioPos, 20, 1, BLACK);
            DrawTextEx(fuente, TextFormat("%.2f kg", perro.getPeso()), pesoPos, 20, 1, BLACK);
            DrawTextEx(fuente, dueno , duenoPos, 20, 1, BLACK);
            DrawTextEx(fuente, perro.getPadecimientos().c_str(), padecimientosPos, 20, 1, BLACK);

        EndDrawing();
    }
    
    UnloadTexture(background);
    UnloadTexture(BotonAtras);
    UnloadTexture(BotonCitas);
    return result;
}

