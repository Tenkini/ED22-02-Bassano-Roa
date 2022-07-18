#include "ListaPersonas.hpp"
#include "Persona.hpp"
#include "Nodo.hpp"

ListaPersonas::ListaPersonas(){
    ListaPersonas *lp = new ListaPersonas();
    Nodo *first = nullptr;
}
void ListaPersonas::setFirst(Nodo *n){
    first = n;
}
Nodo* ListaPersonas::getFirst(){
    return first;
}
void ListaPersonas::insertar(Nodo *n){
    //si la lista esta vacia
    if(first == nullptr){
        setFirst(n);
        n->setNext(n);//apuntando a si mismo
    }
    else if (first->getNext() == first){//si solo tiene un nodo la lista
        first->setNext(n);
        n->setNext(first);
    } else {//insertar al final
        Nodo *aux = first->getNext();
        while (aux != first)
        {
            aux = aux->getNext();
        }
        aux->setNext(n);
        n->setNext(first);
    }
}
void ListaPersonas::eliminar(Nodo *n){
    if(first == nullptr){//lista vacia
        return;
    } else if(first->getNext() == first && n == first){//1 solo nodo y n corresponde al first
        delete(n);
        first = nullptr;
    } else if(n == first && first->getNext() != first){//n a borrar es first pero hay mas de 1 nodo
        Nodo *aux = first;
        first = first->getNext();
        delete(aux);
    } else {//si el nodo a eliminar no es el primero y hay mas de 1 nodo
        Nodo *aux = first;
        do
        {
            if(aux->getNext() == n){
                aux->setNext(aux->getNext()->getNext());
                aux = aux->getNext();
                delete(aux);
            }
        } while (aux->getNext() != first);
    }
}
