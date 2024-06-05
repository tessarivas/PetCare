#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

using std::to_string;

#include "../clases/Usuario.h"

// ------------------Prototype------------------ //
Evento *DibujarCalendario(int screenWidth, int screenHeight, struct Evento *events);
void DibujarEventos(struct Evento *events,int screenWidth,int screenHeight);
// ------------------Funciones------------------ //
// Dibujar papuCalendario
Evento *DibujarCalendario(int screenWidth, int screenHeight, struct Evento *events){

    //------------------------- FONDO ------------------------------ //
    Texture2D fondo = LoadTexture("../assets/PetCare_Calendario.png"); 
    Vector2 fondoPos;
    fondoPos.x = 0;
    fondoPos.y = 0;

    // Bandera de salida
    bool finish=false;

    //-------------------------Parte Superior------------------------------ // 

    // Titulo de mes
    Rectangle Mes;
    Mes.x=screenWidth*0.03;
    Mes.y=screenHeight * 0.17;
    Mes.width = screenWidth * 0.94;
    Mes.height = screenHeight * 0.03;

    // boton de mes anterior
    Rectangle PrevMonth;
    PrevMonth.x = screenWidth * 0.10;
    PrevMonth.y = screenHeight * 0.17;
    PrevMonth.width = screenWidth * 0.10;
    PrevMonth.height = screenHeight * 0.043;

    // Boton de siguiente mes
    Rectangle NextMonth;
    NextMonth.x = screenWidth * 0.80;
    NextMonth.y = screenHeight * 0.17;
    NextMonth.width = screenWidth * 0.10;
    NextMonth.height = screenHeight*0.043;

    // Bloque de calendario
    // Rectangle Calendario;
    // Calendario.x=screenWidth * 0.03;
    // Calendario.y=screenHeight*0.21;
    // Calendario.width= screenWidth *0.95;
    // Calendario.height= screenHeight * 0.70;

    // ----------------Evento--------------------------
    Rectangle titleEvent;
    titleEvent.x=screenWidth*0.1;
    titleEvent.y=screenHeight*0.625;
    titleEvent.width=screenWidth*0.80;
    titleEvent.height=screenHeight*0.07;

    Rectangle desEvent;
    desEvent.x=screenWidth*0.1;
    desEvent.y=screenHeight*0.705;
    desEvent.width=screenWidth*0.8;
    desEvent.height=screenHeight*0.15;

    // Agregar evento
    Rectangle Agregar;
    Agregar.x=screenWidth * 0.23;
    Agregar.y=screenHeight *0.87;
    Agregar.width=screenWidth * 0.54;
    Agregar.height=screenHeight * 0.08;

    Vector2 addPos;
    addPos.x=Agregar.x;
    addPos.y=Agregar.y;

    //-----------------SALIR--------------------
    Rectangle Return;
    Return.x=screenWidth*0.03;
    Return.y=screenHeight * 0.93;
    Return.width=screenWidth * 0.1;
    Return.height = screenHeight * 0.05;
    
    //--------------------NUMERO DE DIAS-----------------------//
    /*
        13% de espacio entre el lado derecho
        7% de espacio entre los cubos de hacia abajo
    */
    //---------------------------------------------------------//

    //------------CUADROS DE LOS DIAS-----------//
    float wi=0.05;
    float hi=0.27;
    
    Rectangle test;
    test.x=screenWidth*0.05;
    test.y=screenHeight*0.27;
    test.width=screenWidth*0.12;
    test.height=screenHeight*0.06;

    // Slecciono un dia?
    bool daySelected = false;
    
    // El dia que selecciono
    int DiaSeleccionado=0;

    // ---------- Textos ----------- //
    const int MaxCharacter=15;
    const int MaxCharacterDesc=25;
    char title[MaxCharacter+1]={""};
    int titleCharacterCont=0;

    char des[MaxCharacterDesc+1]={""};
    int desCharacterCont=0;

    // ---------- Posicion de textos ----------- //
    Vector2 titlePos;
    titlePos.x=titleEvent.x+10;
    titlePos.y=titleEvent.y+10;

    Vector2 desPos;
    desPos.x=desEvent.x+10;
    desPos.y=desEvent.y+10;
    
    // ---------- Textos ----------- //
    // const char *txtCalendario = {"CALENDARIO"};
    
    //Texto
    // Vector2 calPos;
    // calPos.x=screenWidth * 0.2;
    // calPos.y=screenHeight * 0.04;

    // ---------- MESES ----------- //

    int numMonth=1;
    int numDays=31;

    char month[20][12]= {"ENERO","FEBRERO","MARZO","ABRIL","MAYO","JUNIO","JULIO","AGOSTO","SEPTIEMBRE","OCTUBRE","NOVIEMBRE","DICIEMBRE"};

    int textSize=MeasureText(month[numMonth-1],24);

    Vector2 monthPos;
    monthPos.x=(screenWidth / 2) - (textSize/2);
    monthPos.y=screenHeight *0.2;

    // ---------- Eventos Registrados ----------- //
    // Hitbox
    Rectangle info;
    info.x=screenWidth * 0.87;
    info.y=screenHeight * 0.93;
    info.width=screenWidth * 0.1;
    info.height=screenHeight * 0.043;
    
    // Posicion de textura
    Vector2 infoPos;
    infoPos.x=info.x;
    infoPos.y=info.y;

    // ---------- texto y botones ----------- //

    Texture2D nextm= LoadTexture("../assets/PetCare_BotonAdelante.png");
    
    Texture2D prevM= LoadTexture("../assets/PetCare_BotonAtras.png");

    Texture2D salir = LoadTexture("../assets/PetCare_BotonAtrasAzul.png");

    Texture2D botonAgregar = LoadTexture("../assets/PetCare_BotonAnadir.png");

    Texture2D botonInfo= LoadTexture("../assets/PetCare_BotonMasInformacion.png");

    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    Color Bloque={245,246,243,255};

    // ---------- Extras ----------- //

    // Posicion del mouse
    Vector2 Mouse;
    // Donde hizo click
    Vector2 lastclick={0,0};

    // Evento
    struct Evento *temp=nullptr;

    Color amarillo2 ={234,237,33,255};
    
    Color amarillo1 ={232,234,60,255};
    
    while(finish == false){
        BeginDrawing();
            
            ClearBackground(WHITE);
            Mouse = GetMousePosition();
            

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                lastclick=Mouse;
            }

            // Fondo
            DrawTextureEx(fondo,fondoPos,0.0f,1.0f,WHITE);
            
            // ------------Mes Anterior----------- // 
            // DrawRectangleRec(PrevMonth,YELLOW);
            if(CheckCollisionPointRec(lastclick,PrevMonth)){
                if(numMonth > 1){
                    numMonth--;
                    lastclick={0,0};
                    
                    // Reiniciamos el dia
                    DiaSeleccionado=0;
                    daySelected=false;
                }
            }
            DrawTexture(prevM,PrevMonth.x,PrevMonth.y,WHITE);

            // -----------Siguiente Mes----------- // 
            
            //Hitbox
            // DrawRectangleRec(NextMonth,YELLOW);
            if(CheckCollisionPointRec(lastclick,NextMonth)){
                if(numMonth < 12){
                    numMonth++;
                    lastclick={0,0};

                    DiaSeleccionado=0;
                    daySelected=false;
                }
            }
            // Boton
            DrawTexture(nextm,NextMonth.x,NextMonth.y,WHITE);

            // Par
            if(numMonth % 2 == 0){
                // Febrero
                if(numMonth == 2){
                    
                    numDays=29;
                }
                else{
                    // Agosto en adelante
                    if(numMonth >=8){
                        numDays=31;
                    }
                    else{
                        // Junio y abril
                        numDays = 30;
                    }
                }
            }else{ // Impar
                if(numMonth <=7){ 
                    // Enero hasta julio,
                    numDays=31;
                }else{
                    // Septiembre y noviembre
                    numDays=30;
                }
            }

            // Volver a centrar el texto
            textSize = MeasureText(month[numMonth-1], 40);

            monthPos.x = ((screenWidth - textSize ) / 2 ) +10;
            monthPos.y = Mes.y+2;
            
            // Texto
            DrawTextEx(fuente, month[numMonth-1], monthPos, 40, 1, WHITE);

            // Cuadro de Calendario
            // DrawRectangleRec(Calendario,BLUE);
            
            // Evento-------------------------
            //titulo
            DrawRectangleRec(titleEvent,amarillo1);
            //Descripcion
            DrawRectangleRec(desEvent,amarillo1);

            // Tiene que seleccionar un dia para poder escribir un titulo y descripcion---
            if (daySelected== true)
            {
                if(CheckCollisionPointRec(lastclick,titleEvent))
                {
                    int key = GetCharPressed();
                    // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 122) && (titleCharacterCont <MaxCharacter)) // Solo caracteres entre el 32 y 125
                        {
                            title[titleCharacterCont] = (char)key; // Transformar el caracter de codigo ascii a caracter
                            title[titleCharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                            titleCharacterCont++; // Aumentamos el contador de caracteres
                        }
                        key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
                    {
                        if (titleCharacterCont < 0){
                            // Si la cadena esta vacia no hara nada
                        } else{
                            titleCharacterCont--; // Si no esta vacia eliminara un espacio     
                            title[titleCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                        }
                    }
                }
                
                if(CheckCollisionPointRec(lastclick,desEvent))
                {
                    int key = GetCharPressed();
                    // Verificar si hay presiona mas de 1 caracter en el mismo frame. Saldra del ciclo si no presiona nada, nada = 0
                    while (key > 0)
                    {
                        if ((key >= 32) && (key <= 122) && (desCharacterCont <MaxCharacterDesc)) // Solo caracteres entre el 32 y 125
                        {
                            des[desCharacterCont] = (char)key; // Transformar el caracter de codigo ascii a caracter
                            des[desCharacterCont+1] = '\0'; // Agregar caracter nulo al final de la cadena
                            desCharacterCont++; // Aumentamos el contador de caracteres
                        }
                        key = GetCharPressed();  // Revisamos si hay nuevos caracteres en cola en el mismo frame
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) // Borrar
                    {
                        if (desCharacterCont < 0){
                            // Si la cadena esta vacia no hara nada
                        } else{
                            desCharacterCont--; // Si no esta vacia eliminara un espacio     
                            des[desCharacterCont] = '\0'; // Al ultimo que antes era una letra la sustituimos por el caracter nulo
                        }
                    }
                }
            }

            // Titulo del eveneto
            Vector2 titulo2;
            titulo2.x=titlePos.x-20;
            titulo2.y=titlePos.y-20;

            Rectangle titulo2Re;
            titulo2Re.x=titulo2.x-5;
            titulo2Re.y=titulo2.y-5;
            titulo2Re.width = 60;
            titulo2Re.height = 30;
            

            // titulo
            DrawRectangleRec(titulo2Re,amarillo2);
            DrawTextEx(fuente,"Titulo",titulo2,20,2,BLACK);

            DrawTextEx(fuente,title,titlePos,24,2,BLACK);
            
            Vector2 desc2;
            desc2.x=desPos.x-20;
            desc2.y=desPos.y-20;

            Rectangle desc2Re;
            desc2Re.x=desc2.x-5;
            desc2Re.y=desc2.y-5;
            desc2Re.width=120;
            desc2Re.height=30;
            
            // Asutno de evento
            DrawRectangleRec(desc2Re,amarillo2);
            DrawTextEx(fuente,"Descripcion",desc2,20,2,BLACK);
            DrawTextEx(fuente,des,desPos,24,2,BLACK);
            
            // Agregar evento
            DrawTextureEx(botonAgregar,addPos,0.0f,1.0f,WHITE);

            if(daySelected== true){
                if(CheckCollisionPointRec(lastclick,Agregar)){

                    temp=(struct Evento*)malloc(sizeof(struct Evento));
                    
                    temp->day=DiaSeleccionado;
                    temp->month=numMonth;
                    
                    strcpy(temp->title,title);
                    strcpy(temp->description,des);

                    temp->next=nullptr;
                    temp->prev=nullptr;

                    break;
                }
            }

            // Regresar
            DrawTexture(salir,Return.x+2,Return.y+2,WHITE);


            if(CheckCollisionPointRec(lastclick,Return)){
                break;
            }

            // Mas informacion
            if(events != nullptr){
                DrawTextureEx(botonInfo,infoPos,0.0f,1.0f,WHITE);
                if(CheckCollisionPointRec(lastclick,info)){
                    
                    cout<<"Entro"<<endl;    
                    DibujarEventos(events,screenWidth,screenHeight);
                    
                    lastclick={0,0};
                }
            }
            
            wi=0.05;
            hi=0.27;
            test.x=screenWidth*0.05;
            test.y=screenHeight*0.27;

            // Esta funcion me costo musho alv y tan simple que esta
            /*
                Esta funcion creara un cuadro por cada dia del mes hasta 31,
                Primero dibujara 7 cuadros con separacion hacia la derecha de 13 %
                Luego reiniciara las posicion x a 0.05% y sumara la posicion y por 0.07% de la pantalla
                repetira el proceso cada que alcanze los 7 dias y asi hasta llegar a 31
                
                Una vez detecte que selecciono un cuadro que represente un dia, cambiara la bandera de daySelected a true
                y en otro ciclo, buscara en que ubicacion dio el click y que dia representa esa ubicacion, guardando el dia en
                diaSeleccionado

                Actualizacion, cambie a numDays +1 pq me da wba cambiar todo el codigo y para que dibuje un por cada dia del mes
            */
            for(int i=1;i<=numDays+1;i++)
            {   
                char dayC[5];
                Vector2 dayText;
                dayText.x=test.x+2;
                dayText.y=test.y+2;
                if(CheckCollisionPointRec(lastclick,test))
                {
                    daySelected=true;
                }
                
                DrawRectangleRec(test,BLUE);
                // itoa(i - 1,dayC,10);
                
                DrawTextEx(fuente,dayC,dayText,20,1,BLACK);
                
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
                for(int i=1;i<=numDays+1;i++)
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

                    if(CheckCollisionPointRec(lastclick,test)){
                        DiaSeleccionado=i;
                        cout<<"DIA "<< DiaSeleccionado<<endl;
                    }
                    
                    wi=wi+0.13;
                }
            }
        
        EndDrawing();
    }
    UnloadTexture(fondo);
    UnloadTexture(nextm);
    UnloadTexture(prevM);
    UnloadTexture(botonAgregar);
    UnloadFont(fuente);
    return temp;
}

void DibujarEventos(struct Evento *events,int screenWidth,int screenHeight){
    bool finish = false;

    // Titulo de la pantalla
    Rectangle title;
    title.width = screenWidth *0.8;
    title.height = screenHeight *0.1;
    title.x=(screenWidth - title.width) / 2;
    title.y= screenHeight*0.1;

    // Vector2 titlePos;
    // titlePos.x=title.x;
    // titlePos.y=title.y;

    // Cuadro donde se imprimiran los eventos
    // Rectangle c_events;
    // c_events.x=screenWidth*0.1;
    // c_events.y=screenHeight*0.3;
    // c_events.width=screenWidth*0.8;
    // c_events.height=screenHeight*0.6;
    
    // Cantidad de eventos a imprimir
    int count_events=0;

    struct Evento *temp=events;
    while(temp->next!=nullptr){
        count_events++;
        temp=temp->next;
    }

    /*
        Separacion de 3% de la pantalla (arriba y abajo)
    */

    // Cuadro del evento por separado
    Rectangle c_eventos;
    c_eventos.width=screenWidth*0.7;
    c_eventos.height=screenHeight*0.1;
    c_eventos.x=(screenWidth - c_eventos.width)/2;
    c_eventos.y=screenHeight * 0.32;

    // Posicion del titulo
    Vector2 text_events;
    text_events.x=c_eventos.x +10;
    text_events.y=c_eventos.y+10;
    
    // Posicion del dia
    Vector2 dia_text;
    dia_text.x=c_eventos.x +10;
    dia_text.y=c_eventos.y;
    
    // Posicion de la descripcion
    Vector2 desc_text;
    desc_text.x=c_eventos.x;
    desc_text.y=c_eventos.y+10;

    // Boton de salir
    Rectangle salir;
    salir.width=screenWidth*0.1;
    salir.height=screenHeight*0.05;
    salir.x=screenWidth*0.03;
    salir.y=screenHeight*0.93;

    Vector2 salirPos;
    salirPos.x=salir.x;
    salirPos.y=salir.y;

    Vector2 fondoPos;
    fondoPos.x = 0;
    fondoPos.y = 0;

    // Mouse y click
    Vector2 Mouse;
    Vector2 click;

    // Tamaño del texto en pixeles
    int textSize;

    // Recursos
    Texture2D fondo = LoadTexture("../assets/PetCare_Eventos.png");

    Texture2D Boton_atras = LoadTexture("../assets/PetCare_BotonAtrasAzul.png");
    
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");
    
    Color BlancoOscuro={250,171,17,255};
    
    // Texture2D title_calendario=LoadTexture("../assets/PetCare_CalendarioTope.png");

    // temporales extra
    char tempDay[20];
    char tempMonth[20];
    int diaTemp=0;
    

    while(finish == false){
        BeginDrawing();
        ClearBackground(WHITE);
            
        Mouse=GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            click=Mouse;
        }

        DrawTextureEx(fondo, fondoPos, 0.0f, 1.0f, WHITE);
        
        // Reinicamos los valores
        temp=events;
        c_eventos.y=screenHeight * 0.20;
        text_events.y=c_eventos.y+10;
        
        while(temp != nullptr){
            // Dibujamos el cuadro
            DrawRectangleRec(c_eventos,BlancoOscuro);
            // Dibujamos el texto
            // titulo
                DrawTextEx(fuente,temp->title,text_events,32,1,BLACK);
            // Dia
                textSize=MeasureText(temp->title,32);
                
                dia_text.x=text_events.x + textSize + 8;
                dia_text.y=text_events.y;
                
                diaTemp=dia_text.x;
                
                // Pasamos el dia que originalmente es int, a char
                // origen, destino, en decimal (puede ser 16 para hexadecimal)
                // itoa(temp->day,tempDay,10);
                // itoa(temp->month,tempMonth,10);
                strcat(tempDay,"/");
                strcat(tempDay,tempMonth);

                DrawTextEx(fuente,tempDay,dia_text,32,1,BLACK);

                dia_text.x=dia_text.x+20;

                // DrawTextEx(fuente,tempMonth,dia_text,32,1,BLACK);

                dia_text.x=diaTemp;
            
            // Descripcion
                desc_text.x=text_events.x;
                desc_text.y=text_events.y+34;

                DrawTextEx(fuente,temp->description,desc_text,20,1,BLACK);

            // Sumamos un 3% hacia abajo, es 13 pq le sumo el ancho del cuadro mas 3
            c_eventos.y+=screenHeight* 0.13;
            // Igual con el texto
            text_events.y=c_eventos.y+10;

            // Pasamos al siguiente temp
            temp=temp->next;
        }

        // Salir Rectangulo
        // DrawRectangleRec(salir,BLUE);
        // Salir
        DrawTextureEx(Boton_atras,salirPos,0.0f,1.0f,WHITE);

        if(CheckCollisionPointRec(click,salir)){
            break;
        }
        
    EndDrawing();
    }
    UnloadTexture(fondo);
    UnloadFont(fuente);
    UnloadTexture(Boton_atras);

}
