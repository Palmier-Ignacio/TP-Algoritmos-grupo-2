#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "biblioteca.h"

class Nodo
{
private:
    Biblioteca* biblioteca;
    Nodo* siguiente;

public:
    Nodo(Biblioteca* biblioteca);
    Nodo* getSiguiente() const { return siguiente; }
    void setSiguiente(Nodo* sig) { siguiente = sig; }
    Biblioteca* getBiblioteca() const { return biblioteca; }
};

#endif
