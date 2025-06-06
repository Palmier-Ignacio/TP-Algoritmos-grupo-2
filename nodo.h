#ifndef NODO_H
#define NODO_H

#include <iostream>
#include "biblioteca.h"
using namespace std;

class Nodo {
private:
    Biblioteca *biblioteca;
    Nodo *hijoIzquierda;
    Nodo *hijoDerecha;

public:
    Nodo(Biblioteca* biblioteca);

    Biblioteca* getBiblioteca();

    Nodo* getHijoIzquierda();

    Nodo* getHijoDerecha() ;

    void setHijoIzquierda(Nodo* nodo);

    void setHijoDerecha(Nodo* nodo);
};


#endif
