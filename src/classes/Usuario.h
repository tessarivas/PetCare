#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using std::cout;
using std::endl;
using std::cin;
using std::string;

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
    
    // Acciones respecto a la cuenta
    virtual void Registrarse(string Nombre, string Email, string Contrasenia, string Telefono);
    virtual void IniciarSesion(string Email,string Contrasenia);
    virtual void RecuperarContr(string Email);
    bool CerrarSesion();
    void EliminarCuenta();
    
    // Id
    virtual int GenID ();
};

int Usuario::GenID(){
    cout<<"genera la id";
    int id;
    id = rand()% (9999-0+1)-0;
    if ( id <= 999 ){ // No alcanza los 4 digitos
        if ( id <= 99 ) { // No alcanza ni los 3 digitos
            if ( id <= 9 ){ // No alcanza ni los 2 digitos
                // agregar 0 necesarios
            } 
        }
    }
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

