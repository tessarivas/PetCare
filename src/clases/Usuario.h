#include <iostream>
using std::string;
class Usuario
{
protected:
    string Nombre="";
    string Email="";
    string Contrasenia="";
    string Telefono="";
    int FotoPerfil[6];
    
public:
    Usuario();
    virtual void Registrarse(string Nombre, string Email, string Contrasenia, string Telefono);
    virtual void IniciarSesion(string Email,string Contrasenia);
    virtual void RecuperarContr(string Email);
    bool CerrarSesion();
    void EliminarCuenta();
};


