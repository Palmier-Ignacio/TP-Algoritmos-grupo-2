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
    //constructor
    Nodo(Biblioteca* biblioteca);
    //pos: devuelve la biblioteca que tiene guardada el nodo
    Biblioteca* getBiblioteca();
    //pos: devuelve el puntero al hijo izquierda que tiene el nodo
    Nodo* getHijoIzquierda();
    //pos: devuelve el puntero al hijo derecho que tiene el nodo
    Nodo* getHijoDerecha() ;
    //pos: setea el puntero del hijo izquierdo que tiene el nodo
    void setHijoIzquierda(Nodo* nodo);
    //pos: setea el puntero del hijo derecho que tiene el nodo
    void setHijoDerecha(Nodo* nodo);
};


#endif
