#include "Nodo.hpp"
#include "Persona.hpp"

Nodo::Nodo(Persona p){
    Persona persona = p;
    Nodo *next = nullptr;
};
Nodo *Nodo::getNext(){
    return next;
};
void Nodo::setNext(Nodo *n){
    next = n;
};
Persona Nodo::getPersona(){
    return *persona;
};