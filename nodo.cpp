#include <iostream>
#include "biblioteca.h"
#include "nodo.h"
using namespace std;

Nodo::Nodo(Biblioteca *biblioteca)
{
    this->biblioteca = biblioteca;
    this->hijoIzquierda = nullptr;
    this->hijoDerecha = nullptr;
}
// devuelve la biblioteca guardada
Biblioteca *Nodo::getBiblioteca()
{
    return biblioteca;
}

// devuelve el nodo guardado en hijo izq
Nodo *Nodo::getHijoIzquierda()
{
    return hijoIzquierda;
}

// devuelve el nodo guardado en hijo der
Nodo *Nodo::getHijoDerecha()
{
    return hijoDerecha;
}

// setea hijo izq con un nodo dado
void Nodo::setHijoIzquierda(Nodo *nodo)
{
    hijoIzquierda = nodo;
}

// setea hijo der con un nodo dado
void Nodo::setHijoDerecha(Nodo *nodo)
{
    hijoDerecha = nodo;
}
