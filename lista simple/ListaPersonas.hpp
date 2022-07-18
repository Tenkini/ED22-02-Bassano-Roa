#ifndef LISTAPERSONAS_H
#define LISTAPERSONAS_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "Persona.hpp"
#include "Nodo.hpp"

class ListaPersonas
{
private:
    Nodo *first;
public:
    ListaPersonas::ListaPersonas();
    Nodo* getFirst();
    void setFirst(Nodo*);
    void insertar(Nodo*);
    void eliminar(Nodo*);
};

#endif