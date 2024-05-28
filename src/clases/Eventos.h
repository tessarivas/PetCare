#pragma once

#include "Usuario.h"

class Eventos{
public:
    int day;
    string title_event;
    string decription;

    Eventos * next;
    Eventos * prev;

    Eventos();

    void add_event(int day, string title,string description);
};

void Eventos::add_event(int day, string title, string description){
    this->day=day;
    this->title_event=title;
    this->decription=description;
}

Eventos::Eventos(){
    this->day=1;
    this->title_event = "Evento de prueba";
    this->decription = "Ahi vaaa avr";
}
