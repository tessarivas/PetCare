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
#include "functions/Mascota.h"
#include "functions/Sesion.h"


using std::cout;
using std::endl;
using std::string;
// DEFINICIONES PARA FUNCIONES CON MAS DE 1 RETORNO
using std::pair;
using std::make_pair;

// DEFINICIONES
#define ANCHO 414
#define ALTO 896

// PANTALLAS DE LA APP
typedef enum Pantalla{
    // Seleccion de iniciar sesion o registrarse
    INICIO = 0,
    // Nombre y contrasena
    INICIAR_SESION,
    // Nombre de usuario, contraseña
    NUEVO_USUARIO1,
    // Correo electronico y numero de celular
    NUEVO_USUARIO2,
    // Nombre real, apellidos y Fecha de nacimiento
    NUEVO_USUARIO3,
    // Avatares
    CREAR_DUENO, 
    // Lista de mascotas
    MIS_MASCOTAS,
    // ---------REGISTRAR MASCOTA-------- // 
    CREAR_MASCOTA,
    REGISTRAR_PERRO,
    REGISTRAR_GATO,
    // AVATAR
    AVATAR_PERRO,
    AVATAR_GATO,
    // ------- PANTALLAS DE LA MASCOTA ----------- //
    MI_PERFIL,
    CALENDARIO,
    // Cartilla medica
    CARTILLA_MEDICA_DATOS,
    CARTILLA_MEDICA,
    AGREGAR_CITA
} Pantalla;

//------------------Load And Unload Content----------------------------------------//
Cargas CargarContenido(Pantalla actual, Cargas archivos);
void DescargarContenido(Pantalla pantalla_actual, Cargas archivos);

//----------------------------Inicio-----------------------------------------------//
int DibujarInicio(Cargas archivos,int screenWidth, int screenHeight);

pair<Texture2D, bool> DibujarSeleccionDeAvatar(Cargas archivos,int screenWidth,int screenHeight);

pair<Pantalla, bool> MiPerfil(Cargas archivos,int screenWidth, int screenHeight, Dog perro);
//---------------------------------------------------------------------------------//

// INT MAIN, MANEJO DE CASOS, ETC...
int main()
{
    // Ventana
    InitWindow(ANCHO, ALTO, "PetCare");
    SetTargetFPS(60);
    Image icono = LoadImage("../assets/PetCare_LOGO.png");
    SetWindowIcon(icono);
    // Iniciar pantallas
    Pantalla pantalla_actual = AGREGAR_CITA;
    Cargas fondo_actual;
    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
    // Eventos
    Evento *event = nullptr;
    Cita *date = nullptr;
    Cita **agendar = &date; // Acceder al contenido de date
    
    // Variables temporales
    int tempDia;
    int tempMes;
    
    char tempTitle[20];
    char tempDesc[50];
    bool seleccion;

    // Random
    srand(time(NULL));
    // Usuario
    Usuario user; // Usuario actual
    
    // Mascota temporal
    Dog perro;
    // Dog *lista=nullptr;
    Dog *lista = new (Dog);
    lista=nullptr;

    /*1 = gato, 2 = perro*/
    int mascota_actual;

    // PROGRAMA PRINCIPAL
    while(!WindowShouldClose()){
        BeginDrawing();

        switch(pantalla_actual)
        {
            case INICIO:
            {
                int op;
                op = DibujarInicio(fondo_actual,ANCHO,ALTO);
                if(op == 1){
                    // Iniciar sesion
                    pantalla_actual = INICIAR_SESION;
                }
                else
                {
                    if(op==2){
                        pantalla_actual = NUEVO_USUARIO1;
                    }
                }
                DescargarContenido(INICIO,fondo_actual);
                break;
            }
            case INICIAR_SESION:
            {
                // Carga las imagenes en la propia funcion
                user = IniciarSesion(ANCHO,ALTO);
                
                // Acutalizamos pantallas
                pantalla_actual=CREAR_DUENO;
                break;
            }
            case NUEVO_USUARIO1:
            {
                // Carga las imagenes en la propia funcion
                user = RegistrarUsuario(ANCHO,ALTO);

                pantalla_actual=CREAR_DUENO;
                break;
            }
            case CREAR_DUENO: // Avatares
            {
                fondo_actual = CargarContenido(pantalla_actual,fondo_actual);
                
                // Retornara el avatar seleccionado y una bandera
                auto[avatar, regresar] = DibujarSeleccionDeAvatar(fondo_actual, ANCHO, ALTO);
                
                // asignamos el avatar del usuario
                user.avatar=avatar;

                // Si regresar es true, regresa a la pantalla de inicio,en caso de que no continua a mis mascotas
                if(regresar == true){
                    DescargarContenido(CREAR_DUENO, fondo_actual);
                    pantalla_actual = INICIO;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                } else {
                    DescargarContenido(CREAR_DUENO, fondo_actual);
                    pantalla_actual = MIS_MASCOTAS;
                }
                break;
            }
            case MIS_MASCOTAS:
            {
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);

                perro = DibujarMisMascotas(fondo_actual,lista,user,ANCHO,ALTO);
                
                // No carga nada por lo tanto perro se queda con el constructor default y comparamos si es diferente de el default
                string defaultt = "GoldenIsaac";
                if(perro.Nombre == defaultt){
                    pantalla_actual=CREAR_MASCOTA;
                }
                else
                {   
                    pantalla_actual = MI_PERFIL;
                }
                
                DescargarContenido(MIS_MASCOTAS, fondo_actual);

                event=nullptr;
                date=nullptr;
                
                // pantalla_actual = CREAR_MASCOTA;
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case CREAR_MASCOTA:
            {
                mascota_actual = DibujarCrearMascota(fondo_actual,ANCHO,ALTO);
                DescargarContenido(CREAR_MASCOTA,fondo_actual);
                
                if(mascota_actual == 1){
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
                Dog temp_perro;
                RegistrarDogResult result = RegistrarDog(fondo_actual, ANCHO, ALTO, temp_perro);

                DescargarContenido(pantalla_actual, fondo_actual);

                if (result == AVANZAR) {
                    perro = temp_perro;
                    perro.event = nullptr;
                    perro.date=nullptr;
                    pantalla_actual = AVATAR_GATO;
                } else if (result == REGRESAR) {
                    pantalla_actual = CREAR_MASCOTA;
                }
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case REGISTRAR_PERRO:
            {
                Dog temp_perro;
                RegistrarDogResult result = RegistrarDog(fondo_actual, ANCHO, ALTO, temp_perro);

                DescargarContenido(pantalla_actual, fondo_actual);

                if (result == AVANZAR) {
                    perro = temp_perro;
                    perro.event = nullptr;
                    perro.date=nullptr;
                    pantalla_actual = AVATAR_PERRO;
                } else if (result == REGRESAR) {
                    pantalla_actual = CREAR_MASCOTA;
                }
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case AVATAR_GATO:
            {
                perro.Avatar = SeleccionarAvatarPerro(fondo_actual,ANCHO,ALTO);

                lista->add(lista,perro.Nombre,perro.Raza,perro.Dia,perro.Mes,perro.Anio,perro.Peso,perro.Padecimientos,perro.Avatar);
                
                user.DefineMascota(lista);

                // DescargarContenido(pantalla_actual,fondo_actual);
                pantalla_actual = MI_PERFIL;
                
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case AVATAR_PERRO:
            {
                perro.Avatar = SeleccionarAvatarPerro(fondo_actual,ANCHO,ALTO);

                // Agregar el perro nuevo a la lista
                lista->add(lista,perro.Nombre,perro.Raza,perro.Dia,perro.Mes,perro.Anio,perro.Peso,perro.Padecimientos,perro.Avatar);

                user.DefineMascota(lista);

                // DescargarContenido(pantalla_actual,fondo_actual);
                pantalla_actual = MI_PERFIL;

                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                break;
            }
            case MI_PERFIL:
            {   
                fondo_actual = CargarContenido(pantalla_actual, fondo_actual);

                auto[nuevaPantalla, regresar] = MiPerfil(fondo_actual, ANCHO, ALTO, perro);
                
                if(regresar){
                    // VOLVER PANTALLA ANTERIOR (Saltandome lo de la creacion)
                    DescargarContenido(MI_PERFIL, fondo_actual);
                    pantalla_actual = MIS_MASCOTAS;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                } else {
                    // Si no se debe regresar, establecer la nueva pantalla
                    DescargarContenido(MI_PERFIL, fondo_actual);
                    pantalla_actual = nuevaPantalla;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                DescargarContenido(MI_PERFIL, fondo_actual);
                break;
            }
            case CALENDARIO:
            {
                // Evento temporal
                Evento *tempEvent=nullptr;

                // Carga y descarga en la propia funcion
                tempEvent = DibujarCalendario(ANCHO, ALTO, perro.event);

                if(tempEvent !=nullptr){
                    // Escribio eventos
                    // Dia temporal para transferir el dia a la estructura
                    tempDia = tempEvent->day;
                    // Dia temporal para transferir el mes a la estructura
                    tempMes = tempEvent->month;
                    
                    tempTitle[20];
                    strcpy(tempTitle,tempEvent->title);
                    
                    tempDesc[50];
                    strcpy(tempDesc,tempEvent->description);

                    // Agregar el evento nuevo a la lista de eventos
                    
                    addEvent(&event,tempDia,tempMes,tempTitle,tempDesc);
                    
                    perro.DefineEvents(event);
                    cout<<perro.event->title<<endl;
                    cout<<perro.event->title<<endl;
                    cout<<perro.event->title<<endl;

                    lista->addEventDog(lista,event,perro);

                    DibujarEventos(perro.event,ANCHO,ALTO);
                }
                else{
                    // No escribio ningun evento
                }

                pantalla_actual = MI_PERFIL;
                break;
            }
            case CARTILLA_MEDICA_DATOS:
            {
                const char *dueno = user.UserName.c_str();
                RegistrarAccionCita result = DibujarDatosMedicos(perro,dueno, ANCHO, ALTO);
                // CAMBIO DE PANTALLA DEPENDE LA SELECCION
                if (result == ADELANTE) 
                {
                    DescargarContenido(pantalla_actual, fondo_actual);
                    pantalla_actual = CARTILLA_MEDICA;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                } 
                else if (result == ATRAS) 
                {
                    DescargarContenido(pantalla_actual, fondo_actual);
                    pantalla_actual = MI_PERFIL;
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual);
                }
                break;
            }
            case CARTILLA_MEDICA: 
            {
                // Dibujar la pantalla CARTILLA_MEDICA y los botones correspondientes
                int boton_click = DibujarCartillaMedica(perro.date, ANCHO, ALTO);
                
                // Verificar si el usuario hizo clic en el botón ATRAS
                if (boton_click == 1) {
                    DescargarContenido(CARTILLA_MEDICA, fondo_actual);
                    pantalla_actual = CARTILLA_MEDICA_DATOS; // Cambiar a la pantalla MI_PERFIL
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual); // Cargar contenido de la nueva pantalla
                }
                // Verificar si el usuario hizo clic en el botón AGREGAR_CITA
                else if (boton_click == 2) {
                    DescargarContenido(CARTILLA_MEDICA, fondo_actual);
                    pantalla_actual = AGREGAR_CITA; // Cambiar a la pantalla AGREGAR_CITA
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual); // Cargar contenido de la nueva pantalla
                }
                break;
            }
            case AGREGAR_CITA:
            {
                auto result = DibujarAgregarCita(&date, ANCHO, ALTO);

                // Verificar si la bandera de regresar es verdadera
                if (result.second) {
                    DescargarContenido(AGREGAR_CITA, fondo_actual);
                    pantalla_actual = CARTILLA_MEDICA; // Cambiar a la pantalla CARTILLA_MEDICA
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual); // Cargar contenido de la nueva pantalla
                }
                // Verificar si el usuario hizo clic en el botón AÑADIR
                else {
                    perro.DefineDate(date);
                    lista->addDateDog(lista,date,perro);

                    cout<<perro.date->titulo<<endl;
                    DescargarContenido(AGREGAR_CITA, fondo_actual);
                    // Aquí puedes implementar la lógica para agregar una cita
                    pantalla_actual = CARTILLA_MEDICA; // Cambiar a la pantalla CARTILLA_MEDICA
                    fondo_actual = CargarContenido(pantalla_actual, fondo_actual); // Cargar contenido de la nueva pantalla
                }
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
            archivos.FondoInicio = LoadTexture("../assets/VA/PetCareInicioVA.png");
            
            break;
        }
        case INICIAR_SESION:
        {
            archivos.Background=LoadTexture("../assets/VA/PetCareIniciarSesionVA.png");
            break;
        }
        case CREAR_DUENO:
        {
            archivos.FondoCrearDueno = LoadTexture("../assets/PetCare_CrearDueno2.png");
            archivos.BotonListo = LoadTexture("../assets/PetCare_BotonListo.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.Avatar1 = LoadTexture("../assets/PetCare_Avatares/1.png");
            archivos.Avatar2 = LoadTexture("../assets/PetCare_Avatares/2.png");
            archivos.Avatar3 = LoadTexture("../assets/PetCare_Avatares/3.png");
            archivos.Avatar4 = LoadTexture("../assets/PetCare_Avatares/4.png");
            archivos.Avatar5 = LoadTexture("../assets/PetCare_Avatares/5.png");
            archivos.Avatar6 = LoadTexture("../assets/PetCare_Avatares/6.png");
            archivos.fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");
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
            break;
        }
        case REGISTRAR_GATO:
        {
            archivos.FondoRegPerro = LoadTexture("../assets/PetCare_MiGatoDatos.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonAdelante = LoadTexture("../assets/PetCare_BotonAdelante.png");
            break;
        }
        case AVATAR_PERRO:
        {
            archivos.Background = LoadTexture("../assets/PetCare_MiPerroAvatar.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonMas = LoadTexture("../assets/PetCare_BotonMas.png");
            archivos.PERRO1 = LoadTexture("../assets/PetCare_Perros/1.png");
            archivos.PERRO2 = LoadTexture("../assets/PetCare_Perros/2.png");
            archivos.PERRO3 = LoadTexture("../assets/PetCare_Perros/3.png");
            archivos.PERRO4 = LoadTexture("../assets/PetCare_Perros/4.png");
            archivos.PERRO5 = LoadTexture("../assets/PetCare_Perros/5.png");
            archivos.PERRO6 = LoadTexture("../assets/PetCare_Perros/6.png");
            archivos.PERRO7 = LoadTexture("../assets/PetCare_Perros/7.png");
            archivos.PERRO8 = LoadTexture("../assets/PetCare_Perros/8.png");
            break;
        }
        case AVATAR_GATO:
        {
            archivos.Background = LoadTexture("../assets/PetCare_MiGatoAvatar.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonMas = LoadTexture("../assets/PetCare_BotonMas.png");
            archivos.PERRO1 = LoadTexture("../assets/PetCare_Gatos/1.png");
            archivos.PERRO2 = LoadTexture("../assets/PetCare_Gatos/2.png");
            archivos.PERRO3 = LoadTexture("../assets/PetCare_Gatos/3.png");
            archivos.PERRO4 = LoadTexture("../assets/PetCare_Gatos/4.png");
            archivos.PERRO5 = LoadTexture("../assets/PetCare_Gatos/5.png");
            archivos.PERRO6 = LoadTexture("../assets/PetCare_Gatos/6.png");
            archivos.PERRO7 = LoadTexture("../assets/PetCare_Gatos/7.png");
            archivos.PERRO8 = LoadTexture("../assets/PetCare_Gatos/8.png");
            break;
        }
        case MI_PERFIL:
        {
            archivos.FondoMiMascota = LoadTexture("../assets/PetCare_MiPerfil.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonMiInfo = LoadTexture("../assets/PetCare_BotonMiInfo.png");
            archivos.BotonCartilla = LoadTexture("../assets/PetCare_BotonCartillaMedica.png");
            archivos.BotonCalendario = LoadTexture("../assets/PetCare_BotonCalendario.png");
            break;
        }
        case CALENDARIO:
        {
            archivos.FondoCalendario = LoadTexture("../assets/PetCare_Calendario.png");
            archivos.BotonAtras = LoadTexture("../assets/PetCare_BotonAtras.png");
            archivos.BotonAdelanteAzul = LoadTexture("../assets/PetCare_BotonAdelanteAzul.png");
            archivos.BotonAtrasAzul = LoadTexture("../assets/PetCare_BotonAtrasAzul.png");
            archivos.BotonAnadir = LoadTexture("../assets/PetCare_BotonAnadir.png");
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
        
    }
    if(pantalla_actual==INICIAR_SESION){
        UnloadTexture(archivos.Background);
    }
    if(pantalla_actual == CREAR_DUENO){
        UnloadTexture(archivos.FondoCrearDueno);
        UnloadTexture(archivos.BotonListo);
        UnloadTexture(archivos.BotonAtras);
        // UnloadTexture(archivos.Avatar1);
        // UnloadTexture(archivos.Avatar2);
        // UnloadTexture(archivos.Avatar3);
        // UnloadTexture(archivos.Avatar4);
        // UnloadTexture(archivos.Avatar5);
        // UnloadTexture(archivos.Avatar6);
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
    if(pantalla_actual == REGISTRAR_GATO){
        UnloadTexture(archivos.FondoRegGato);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonAdelante);
    }
    if(pantalla_actual == AVATAR_PERRO){
        UnloadTexture(archivos.FondoAvatarPerro);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonMas);
        UnloadTexture(archivos.PERRO1);
        UnloadTexture(archivos.PERRO2);
        UnloadTexture(archivos.PERRO3);
        UnloadTexture(archivos.PERRO4);
        UnloadTexture(archivos.PERRO5);
        UnloadTexture(archivos.PERRO6);
        UnloadTexture(archivos.PERRO7);
        UnloadTexture(archivos.PERRO8);
    }
    if(pantalla_actual == AVATAR_GATO){
        UnloadTexture(archivos.FondoAvatarGato);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonMas);
        UnloadTexture(archivos.PERRO1);
        UnloadTexture(archivos.PERRO2);
        UnloadTexture(archivos.PERRO3);
        UnloadTexture(archivos.PERRO4);
        UnloadTexture(archivos.PERRO5);
        UnloadTexture(archivos.PERRO6);
        UnloadTexture(archivos.PERRO7);
        UnloadTexture(archivos.PERRO8);
    }
    if(pantalla_actual == MI_PERFIL){
        UnloadTexture(archivos.FondoMiMascota);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonMiInfo);
        UnloadTexture(archivos.BotonCartilla);
        UnloadTexture(archivos.BotonCalendario);
    }
    if(pantalla_actual == CALENDARIO){
        UnloadTexture(archivos.FondoCalendario);
        UnloadTexture(archivos.BotonAtras);
        UnloadTexture(archivos.BotonAdelanteAzul);
        UnloadTexture(archivos.BotonAtrasAzul);
        UnloadTexture(archivos.BotonAnadir);
    }
}

// 1=Iniciar sesion, 2.-registrar, 0=error DIBUJAR LA PANTALLA DE INICIO CON LA QUE ENTRARA
int DibujarInicio(Cargas archivos, int screenWidth, int screenHeight) 
{
    // Iniciar sesion
    Rectangle sesion;
    sesion.width = screenWidth *0.62;
    sesion.height = screenHeight *0.078;
    sesion.x=(screenWidth - sesion.width) / 2;
    sesion.y=screenHeight * 0.795;

    // Color rojo transparente
    Color trans ={255,0,0,100};

    // Registrarse
    Rectangle registrar;
    registrar.width = screenWidth *0.62;
    registrar.height = screenHeight *0.06;
    registrar.x=(screenWidth - registrar.width) / 2;
    registrar.y=screenHeight * 0.9;

    Vector2 Mouse;
    Vector2 click;

    while(true){
        // FONDO DE INICIO
        BeginDrawing();
            Mouse = GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                click=Mouse;
            }

            DrawTextureEx(archivos.FondoInicio, archivos.Position, 0.0f, 1.0f, WHITE);


            if(CheckCollisionPointRec(click,sesion)){
                return 1;
            }
            
            if(CheckCollisionPointRec(click,registrar)){
                return 2;
            }
        EndDrawing();
    }

    return 0;
}

// Seleccionar avatar para el usuario
pair<Texture2D, bool> DibujarSeleccionDeAvatar(Cargas archivos,int screenWidth,int screenHeight)
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
    listo.width = screenWidth * 0.55;
    listo.height = screenHeight * 0.1;
    listo.y = screenHeight * 0.75;
    listo.x = (screenWidth/2) - (listo.width/2);

    // Cuadro de avatares
    Rectangle c_avatares;
    c_avatares.x=(tamano_fondo - 320 )/2;
    c_avatares.y=screenHeight * 0.40;
    c_avatares.width=320;
    c_avatares.height=225;

    // HitBox de avatares
    Rectangle Avatar[6];

    bool selected=false;

    for(int i = 0; i < 6; i++){
        Avatar[i].x = screenWidth * ((i % 3 == 0) ? 0.15f : (i % 3 == 1) ? 0.40f : 0.66f);
        if(i <3){
            Avatar[i].y = screenHeight * 0.41;
        }
        else
        {
            Avatar[i].y = screenHeight * 0.54;
        }
        Avatar[i].width = screenWidth * 0.2f;
        Avatar[i].height = screenHeight * 0.1f;
    }

    // Textura de cada avatar
    Texture2D avataresTexturas[6] = { archivos.Avatar1, archivos.Avatar2, archivos.Avatar3, archivos.Avatar4, archivos.Avatar5, archivos.Avatar6 };
    // el avatar que va a regreasr
    Texture2D avatarSelected;
    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            LastClick = Mouse;
        }

        // FONDO
        DrawTextureEx(archivos.FondoCrearDueno,archivos.Position,0.0f,1.0f,WHITE);

        // Verificar si se hizo clic en algun avatar
        for (int i = 0; i < 6; i++) {
            if (CheckCollisionPointRec(LastClick, Avatar[i])){
                avatarSeleccionado = i;
                selected = true;
            }
        }

        // Dibujar los avatares y bordes si estan seleccionados
        for (int i = 0; i < 6; i++){
            if (avatarSeleccionado == i){
                // Dibujar borde de color si esta seleccionado
                DrawRectangleLinesEx(Avatar[i], 8, GREEN);
            }
            DrawTextureEx(avataresTexturas[i], { Avatar[i].x + 5, Avatar[i].y }, 0.0f, 1.0f, WHITE);
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
            if(selected)
            {
                avatarSelected=avataresTexturas[avatarSeleccionado];
                band = true;
            }
            else
            {
                // No a seleccionado un avatar
            }
        }

        EndDrawing();
    } while(band == false);


    return make_pair(avatarSelected, regresar);
}

// DIBUJAR EL PERFIL DE LA MASCOTA CREADA O SELECCIONADA
pair<Pantalla, bool> MiPerfil(Cargas archivos, int screenWidth, int screenHeight, Dog perro) 
{
    bool regresar = false; // Para boton atras
    bool seleccion = false; // Pantalla siguiente
    Pantalla nuevaPantalla = MI_PERFIL;
    
    // AVATAR MASCOTA
    Vector2 AvatarPos;
    AvatarPos.x = screenWidth * 0.2;
    AvatarPos.y = screenHeight * 0.91;
    // BOTON ATRAS
    Rectangle atras;
    atras.width = screenWidth * 0.1;
    atras.height = screenHeight * 0.05;
    atras.y = 20;
    atras.x = 20;
    // BOTON INFO
    Rectangle info;
    info.x = screenWidth * 0.17;
    info.y = screenHeight * 0.27;
    info.width = screenWidth * 0.6;
    info.height = screenHeight * 0.1;
    // BOTON CARTILLA
    Rectangle cartilla;
    cartilla.x = screenWidth * 0.17;
    cartilla.y = screenHeight * 0.27;
    cartilla.width = screenWidth * 0.6;
    cartilla.height = screenHeight * 0.18;
    // BOTON CALENDARIO
    Rectangle calendario;
    calendario.x = screenWidth * 0.17;
    calendario.y = screenHeight * 0.50;
    calendario.width = screenWidth * 0.6;
    calendario.height = screenHeight * 0.18;
    // POSICION DEL TEXTO DE LA MASCOTA
    const char * mascota = perro.Nombre.c_str(); // Transformar a cadena
    Vector2 mascotaPos;
    mascotaPos.x = screenWidth * 0.4;
    mascotaPos.y = screenHeight * 0.92;

    Vector2 Mouse;
    Vector2 LastClick;

    do{
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            LastClick = Mouse;
        }

        // FONDO Y BOTONES
        DrawTextureEx(archivos.FondoMiMascota, archivos.Position,0.0f,1.0f,WHITE);
        DrawTexture(archivos.BotonCartilla, cartilla.x, cartilla.y, WHITE);
        DrawTexture(archivos.BotonCalendario, calendario.x, calendario.y, WHITE);
        DrawTexture(archivos.BotonAtras, atras.x, atras.y, WHITE);

        if (CheckCollisionPointRec(LastClick, cartilla))
        {
            nuevaPantalla = CARTILLA_MEDICA_DATOS;
            seleccion = true;
        }

        if (CheckCollisionPointRec(LastClick, calendario))
        {
            nuevaPantalla = CALENDARIO;
            seleccion = true;
        }

        if (CheckCollisionPointRec(LastClick, atras))
        {
            regresar = true;
            break;
        }

        // AVATAR DEL PERRO
        DrawTextureEx(perro.Avatar, AvatarPos, 0.0f, 0.8f, WHITE);
        // NOMBRE DEL PERRO
        DrawTextEx(archivos.fuente, mascota, mascotaPos, 40.0f, 2.0f, BLACK);

        EndDrawing();
    } while(seleccion == false);

    return make_pair(nuevaPantalla, regresar);
} 

