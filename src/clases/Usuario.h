#pragma once

#include "raylib.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::to_string;

#include "Dog.h"
#include "Citas.h"
#include "Eventos.h"
#include "../functions/Calendario.h"
#include "../functions/CartillaMedica.h"

class Usuario{
public:
    // ---Datos basicos--- //
    string UsuarioID; // identificador
    
    string Nombre="";
    string ApellidoPaterno="";
    string ApellidoMaterno="";
    
    // Cuenta
    string Passwoard="";
    string Email="";

    // Contacto
    string Telefono="";
    int FotoPerfil[6];
    Dog *mascota;

    // Constructores
    Usuario();
    Usuario(string nombre, string email,string passwoard,string telefono);
    void DefineName(string name);
    
    // Id
    virtual string GenID ();
    void GetName();
    void DefineMascota(Dog *mascota);
};

string Usuario::GenID() {
    int idt = rand() % 1000; // Genera un número entre 0 y 9999
    string id = to_string(idt);

    // Si id.anchura es menor a 4 digitos
    while (id.length() < 4) {
        id = "0" + id; // Asegura que el ID tenga 4 dígitos
    }
    id = '#' + id;
    return id;
}

void Usuario::GetName(){
    cout<<this->Nombre<<endl;
}

void Usuario::DefineName(string name){
    this->Nombre = name;
}

Usuario::Usuario(){
    this->UsuarioID = "#000000";
    this->Nombre = "Xochitl";
    this->ApellidoPaterno = "Lozano";
    this->ApellidoPaterno = "Swift";
    this->Email = "xochitl.123@gmail.com";
    this->Passwoard = "xochilt1234";
    this->Telefono = "64612345678";
    this->mascota=nullptr;
}

Usuario::Usuario(string nombre, string email,string passwoard,string telefono){
    this->Nombre=nombre;
    this->Email=email;
    this->Passwoard=passwoard;
    this->Telefono=telefono;
}

void Usuario::DefineMascota(Dog *mascota){
    this->mascota = mascota;
}