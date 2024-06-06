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
#include "../functions/Load.h"

class Usuario{
public:
    // ---Datos basicos--- //
    string UsuarioID; // identificador
    
    string UserName="";

    string Nombre="";
    string ApellidoPaterno="";
    string ApellidoMaterno="";
    
    Texture2D avatar;
    
    // Cuenta
    string Passwoard="";
    string Email="";

    // Contacto
    string Telefono="";
    
    // Mascotas
    Dog *mascota;

    // Constructores
    Usuario();
    Usuario(string nombre, string email,string passwoard,string telefono);
    
    // ------ Define ------- //
    void DefineName(string name);
    void DefineName(char name[]);
    
    void DefinePas(char pas[]);
    void DefinePas(string pas);
    
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

void Usuario::DefineName(char name[]){
    this->Nombre = string(name);
}

void Usuario::DefinePas(string pas){
    this->Nombre = pas;
}

void Usuario::DefinePas(char pas[]){
    this->Nombre = string(pas);
}


Usuario::Usuario(){
    this->UsuarioID = "#000000";
    this->UserName = "Xx_Xochitl_xX";

    this->Nombre = "Xochitl";
    this->ApellidoPaterno = "Lozano";
    this->ApellidoPaterno = "Swift";
    
    this->Email = "xochitl.123@gmail.com";
    this->Passwoard = "xochilt1234";
    this->Telefono = "64612345678";
    
    this->avatar = LoadTexture("../assets/PetCare_Avatares/1.png");
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