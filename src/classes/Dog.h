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
