#pragma once

#include "Usuario.h"

struct Evento{
    int day;
    int month;
    char title[20];
    char description[60];
    struct Evento *next, *prev;
};

struct Evento * createNodo (int day,int month,string title, string description);
void addEvent(struct Evento **event, int day, int month, string title, string description);

struct Evento * createNodo (int day,int month,char title[], char description[]){
    struct Evento *nodo = (struct Evento*)malloc(sizeof(struct Evento));
    nodo->day=day;
    nodo->month=month;
    
    strcpy(nodo->title,title);
    strcpy(nodo->description,description);
    
    nodo->next=nullptr;
    nodo->prev=nullptr;
    return nodo;
}

void addEvent(struct Evento **event, int day, int month, char title[], char description[]){
    struct Evento *nodo = createNodo(day,month,title,description);
    if (*event == nullptr){
        *event = nodo;
    }
    else{
        struct Evento *temp=*event;
        while(temp->next !=nullptr){
            temp=temp->next;
        }
        temp->next=nodo;
        nodo->prev=temp;
    }
}

void liberar(struct Evento *event){
    free(event);
}


void pri (struct Evento *head)
{
    struct Evento *temp = head;
    while(temp!=NULL)
    {
        cout<<temp->day<<" "<<temp->title<<" "<<temp->description<<" "<<endl;
        temp=temp->next;
    }
}