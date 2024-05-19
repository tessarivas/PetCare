#pragma once

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

class Usuario{
protected:
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
    int FotoPerfil[6]; // Todavia falta saber como subir una foto personalizada
    
public:
    // Constructores
    Usuario();
    Usuario(string nombre, string email,string passwoard,string telefono);
    void DefineName(string name);
    
    // // Acciones respecto a la cuenta
    // virtual void Registrarse(string Nombre, string Email, string Contrasenia, string Telefono);
    // virtual void IniciarSesion(string Email,string Contrasenia);
    // virtual void RecuperarContr(string Email);
    // bool CerrarSesion();
    // void EliminarCuenta();
    
    // Id
    virtual string GenID ();
    void GetName();
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
}

Usuario::Usuario(string nombre, string email,string passwoard,string telefono){
    this->Nombre=nombre;
    this->Email=email;
    this->Passwoard=passwoard;
    this->Telefono=telefono;
}

// void Registrarse(string Nombre, string Email, string Contrasenia, string Telefono){

// }

// void IniciarSesion(string Email,string Contrasenia){

// }

// void RecuperarContr(string Email){

// }

// bool CerrarSesion(){
//     return false;
// }

// void EliminarCuenta(){

// }
