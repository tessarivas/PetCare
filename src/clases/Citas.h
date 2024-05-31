// Citas.h

#pragma once
#include "Usuario.h"

typedef struct Cita{
    int dia;
    int mes;
    char titulo[15];
    char descripcion[60];
    bool seleccion;
    Cita *siguiente, *anterior;
} Cita;

// DEFINICIONES
Cita *CrearNodo (int dia,int mes,char titulo[], char descripcion[], bool seleccion);
void AgregarCita(Cita **CitaAgendada, int dia, int mes, char titulo[], char descripcion[], bool seleccion);
void liberar(Cita *CitaAgendada);

// CREAR NODO
Cita *CrearNodo(int dia,int mes,char titulo[], char descripcion[], bool seleccion){
    Cita *nodo = (Cita*)malloc(sizeof(Cita));
    nodo->dia=dia;
    nodo->mes=mes;
    
    strcpy(nodo->titulo,titulo);
    strcpy(nodo->descripcion,descripcion);
    
    nodo->siguiente=nullptr;
    nodo->anterior=nullptr;
    return nodo;
}

// AGREGAR CITA NUEVA
void AgregarCita(struct Cita **CitaAgendada, int dia, int mes, char titulo[], char descripcion[], bool seleccion){
    Cita *nodo = CrearNodo(dia,mes,titulo,descripcion, seleccion);
    if (*CitaAgendada == nullptr){
        *CitaAgendada = nodo;
    }
    else{
        Cita *temp=*CitaAgendada;
        while(temp->siguiente !=nullptr){
            temp=temp->siguiente;
        }
        temp->siguiente=nodo;
        nodo->anterior=temp;
    }
}

// LIBERAR MEMORIA
void liberar(Cita *CitaAgendada){
    free(CitaAgendada);
}