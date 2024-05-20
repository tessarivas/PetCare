#pragma once

#include "Usuario.h"

class Cat{
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
    //Los padecimientos podemos hacerlo en una estructura de datos para poder poner mas de uno, pero eso ya despues :b

    //Constructor
    Cat();
    Cat(string name, string raza, int dia, int mes, int anio,float peso, string Padecimientos);

    // Gets
    string getName();
    string getRaza();
    int getDia();
    int getMonth();
    int getYear();
    float getPeso();
    string getPadecimientos();

};

//--------------------Funciones----------------------//
// Constructor
Cat::Cat(){
    this->Nombre = "HaroGato";
    this->Raza = "Naranja";
    this->Dia = 1;
    this->Mes = 1;
    this->Anio = 2024;
    this->Peso = 3.2;
    this->Padecimientos = "Ninguno";
}

Cat::Cat(string name, string raza, int dia, int mes, int anio,float peso, string padecimientos){
    this->Nombre = name;
    this->Raza = raza;
    this->Dia = dia;
    this->Mes = mes;
    this->Anio = anio;
    this->Peso = peso;
    this->Padecimientos = padecimientos;
}

// Gets
string Cat::getName(){
    return this->Nombre;
}

string Cat::getRaza(){
    return this->Raza;
}
