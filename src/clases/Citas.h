// Citas.h
#pragma once
#include "Usuario.h"

using std::string;

typedef struct Cita{
    string titulo;
    string descripcion;
    int dia;
    int mes;
    bool esVacuna;
    Cita* siguiente;
    Cita* anterior;
} Cita;

// DEFINICIONES
Cita* CrearNodo(int dia, int mes, const string& titulo, const string& descripcion, bool esVacuna);
void AgregarCita(Cita **CitaAgendada, int dia, int mes, char titulo[], char descripcion[], bool seleccion);
void liberar(Cita *CitaAgendada);

// CREAR NODO
Cita* CrearNodo(int dia, int mes, const string& titulo, const string& descripcion, bool esVacuna) {
    Cita* nodo = new Cita;
    nodo->dia = dia;
    nodo->mes = mes;
    nodo->titulo = titulo;
    nodo->descripcion = descripcion;
    nodo->esVacuna = esVacuna;
    nodo->siguiente = nullptr;
    nodo->anterior = nullptr;
    return nodo;
}


// AGREGAR CITA NUEVA
void AgregarCita(Cita** CitaAgendada, int dia, int mes, const string& titulo, const string& descripcion, bool esVacuna) {
    Cita* nodo = CrearNodo(dia, mes, titulo, descripcion, esVacuna);
    if (*CitaAgendada == nullptr) {
        *CitaAgendada = nodo;
    }
    else {
        Cita* temp = *CitaAgendada;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nodo;
        nodo->anterior = temp;
    }
}

// LIBERAR MEMORIA
void liberar(Cita *CitaAgendada){
    free(CitaAgendada);
}