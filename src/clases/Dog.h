#pragma once

#include "Usuario.h"

class Dog{
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
    //Los padecimientos podemos hacerlo en una estructura de datos para poder poner mas de uno, pero eso ya despues :b

    Dog *next,*prev;

    //Constructor
    Dog();
    Dog(string name, string raza, int dia, int mes, int anio,float peso, string Padecimientos);

    // Gets
    string getName();
    string getRaza();

    // Define
    void DefineAvatar(Texture2D textura);
    void Definir(string name, string raza, int dia, int mes, int anio,float peso, string padecimientos);

    // --------- LISTAS -------- //
    Dog * CreateNodoDog(string name, string raza, int dia, int mes, int anio, float peso, string padecimientos);
    void RegistrarNuevaMascota(Dog *&mascota,string name, string raza, int dia, int mes, int anio, float peso, string padecimientos);
    void addNewMascota(Dog*&destino,Dog *referencia);

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
    this->next=nullptr;
    this->prev=nullptr;
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

// ------ Define ------ //
void Dog::Definir(string name, string raza, int dia, int mes, int anio,float peso, string padecimientos)
{
    this->Nombre = name;
    this->Raza = raza;
    this->Dia = dia;
    this->Mes = mes;
    this->Anio = anio;
    this->Peso = peso;
    this->Padecimientos = padecimientos;
}


//---------------- LOGICA DE LISTA -------------------//

Dog * Dog::CreateNodoDog(string name, string raza, int dia, int mes, int anio, float peso, string padecimientos){
    Dog * nodo = new(Dog);
    nodo->Definir(name,raza,dia,mes,anio,peso,padecimientos);
    return nodo;
}

void Dog::RegistrarNuevaMascota(Dog *&mascota,string name, string raza, int dia, int mes, int anio, float peso, string padecimientos){
    Dog *nodo = CreateNodoDog(name,raza,dia,mes,anio,peso,padecimientos);

    if(mascota == nullptr){
        mascota = nodo;
    }
    else{
        Dog * temp = mascota;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        mascota->prev=temp;
        temp->next=mascota;
    }
}

void Dog::addNewMascota(Dog*&destino,Dog *referencia){
    cout<<"volvio a entraer"<<endl;
    if(destino == nullptr){
        destino = referencia;
    }
    else{
        Dog * temp = destino;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        destino->prev=temp;
        temp->next=destino;
    }
}


// Gets
string Dog::getName(){
    return this->Nombre;
}

string Dog::getRaza(){
    return this->Raza;
}

void Dog::DefineAvatar(Texture2D textura){
    this->Avatar=textura;
}
