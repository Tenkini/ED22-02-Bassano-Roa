#ifndef NODO_H
#define NODO_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "Persona.hpp"

class Nodo
{
private:
    Persona *persona;
    Nodo *next;
public: 
    Nodo(Persona);

    Persona getPersona();
    void setPersona(Persona);
    Nodo* getNext();
    void setNext(Nodo*);
};

#endif