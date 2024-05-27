#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <utility> 

typedef struct Cargas{
    // INICIO
    Texture2D FondoInicio;
    Texture2D BotonEntrar;
    // CREAR DUEÑO
    Texture2D FondoCrearDueno;
    Texture2D BotonListo;
    Texture2D BotonAtras;
    Texture2D Avatar1;
    Texture2D Avatar2;
    Texture2D Avatar3;
    Texture2D Avatar4;
    Texture2D Avatar5;
    Texture2D Avatar6;
    // MIS MASCOTAS
    Texture2D FondoMisMascotas;
    Texture2D BotonAnadir;
    // AÑADIR MASCOTAS
    Texture2D FondoAnadirMascotas;
    Texture2D BotonPerro;
    Texture2D BotonGato;
    // REGISTRAR PERRO
    Texture2D FondoRegPerro;
    Texture2D BotonAdelante;
    // REGISTRAR GATO
    Texture2D FondoRegGato;
    // EXTRAS
    
    // Fondo predeteminado
    Texture2D Background;
    
    // Posicion predeteminada
    Vector2 Position = { 0.0f, 0.0f };
    
    // Fuente
    Font fuente;
    
    // Color de los bloques de texto
    Color Bloque1={245,246,243,255};

} Cargas;