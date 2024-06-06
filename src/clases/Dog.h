#pragma once
#include "Usuario.h"
#include "Eventos.h"
#include "Citas.h"

enum RegistrarDogResult {
    AVANZAR,
    REGRESAR,
    CONTINUAR
};


class Dog
{
public:
    // Datos basicos
    string Nombre;
    string Raza;
    
    // Fecha de nacimiento
    int Dia;
    int Mes;
    int Anio;
    
    //Datos medicos
    float Peso;
    string Padecimientos;
    Texture2D Avatar;

    Dog *next, *prev;
    struct Evento *event;
    struct Cita *date;
    //Los padecimientos podemos hacerlo en una estructura de datos para poder poner mas de uno, pero eso ya despues :b

    //Constructor
    Dog();
    Dog(string name, string raza, int dia, int mes, int anio,float peso, string Padecimientos);

    // Gets
    string getName();
    string getRaza();
    int getDia();
    int getMonth();
    int getYear();
    float getPeso();
    string getPadecimientos();

    // Define
    void DefineAvatar(Texture2D textura);

    // --- Lista --- //
    Dog *createNodo(string name, string raza, int dia, int mes , int anio, float peso, string padecimientos,Texture2D avatar);
    void add(Dog *&lista, string name, string raza, int dia, int mes , int anio, float peso, string padecimientos,Texture2D avatar);
    void DefineEvents(struct Evento *event);
    void DefineDate(struct Cita *date);
    void addEventDog(Dog*&lista, struct Evento *event,Dog perro);
    void addDateDog(Dog*&lista ,struct Cita *date,Dog perro);
};

//--------------------Funciones----------------------//
// Constructor
Dog::Dog(){
    this->Nombre = "GoldenIsaac";
    this->Raza = "Golden Retriever";
    this->Dia = 1;
    this->Mes = 1;
    this->Anio = 2024;
    this->Peso = 5.2;
    this->Padecimientos = "Ninguno";
    this->event=nullptr;
    this->date=nullptr;
    this->next=nullptr;
    this->prev=nullptr;
}

Dog *Dog::createNodo(string name, string raza, int dia, int mes , int anio, float peso, string padecimientos,Texture2D avatar){
    Dog *nodo = new(Dog);
    
    nodo->Nombre = name;
    nodo->Raza=raza;
    
    nodo->Dia=dia;
    nodo->Mes=mes;
    nodo->Anio=anio;
    
    nodo->Peso=peso;
    nodo->Padecimientos=padecimientos;

    nodo->Avatar=avatar;

    nodo->event=nullptr;
    nodo->date=nullptr;
    nodo->next=nullptr;
    nodo->prev=nullptr;
    
    return nodo;
}

void Dog::add(Dog *&lista, string name, string raza, int dia, int mes , int anio, float peso, string padecimientos,Texture2D avatar){
    Dog *nodo = createNodo(name,raza,dia,mes,anio,peso,padecimientos,avatar);

    if(lista==nullptr){
        lista=nodo;
    }
    else{
        Dog *temp = lista;
        while(temp->next != nullptr){
            temp=temp->next;
        }
        nodo->prev=temp;
        temp->next=nodo;
        
        
    }
}

Dog::Dog(string name, string raza, int dia, int mes, int anio,float peso, string padecimientos){
    this->Nombre = name;
    this->Raza = raza;
    this->Dia = dia;
    this->Mes = mes;
    this->Anio = anio;
    this->Peso = peso;
    this->Padecimientos = padecimientos;
}

void Dog::addEventDog(Dog*&lista, struct Evento *event,Dog perro){
    Dog *temp = lista;
    while (temp != nullptr) {
        if (temp->Nombre == perro.Nombre) {
            temp->event = event;
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr && temp->event != nullptr) {
        cout << temp->Nombre << ": " << temp->event->title << endl;
    } else {
        cout << "No se encontró el perro o el evento no se asignó correctamente." << endl;
    }
}

void Dog::addDateDog(Dog*&lista ,struct Cita *date,Dog perro){
    Dog *temp = lista;
    while (temp != nullptr) {
        if (temp->Nombre == perro.Nombre) {
            temp->date = date;
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr && temp->date != nullptr) {
        cout << temp->Nombre << ": " << temp->date->titulo << endl;
    } else {
        cout << "No se encontró el perro o el evento no se asignó correctamente." << endl;
    }
}

void Dog:: DefineEvents(struct Evento *event){
    this->event=event;
}

void Dog:: DefineDate(struct Cita *date){
    this->date=date;
}

// Gets
string Dog::getName(){
    return this->Nombre;
}

string Dog::getRaza(){
    return this->Raza;
}

int Dog::getDia(){
    return this->Dia;
}

int Dog::getMonth(){
    return this->Mes;
}

int Dog::getYear(){
    return this->Anio;
}

float Dog::getPeso(){
    return this->Peso;
}

string Dog::getPadecimientos(){
    return this->Padecimientos;
}

void Dog::DefineAvatar(Texture2D textura){
    this->Avatar = textura;
}