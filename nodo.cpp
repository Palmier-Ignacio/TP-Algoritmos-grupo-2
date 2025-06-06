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

Biblioteca *Nodo::getBiblioteca()
{
    return biblioteca;
}

Nodo *Nodo::getHijoIzquierda()
{
    return hijoIzquierda;
}

Nodo *Nodo::getHijoDerecha()
{
    return hijoDerecha;
}

void Nodo::setHijoIzquierda(Nodo *nodo)
{
    hijoIzquierda = nodo;
}

void Nodo::setHijoDerecha(Nodo *nodo)
{
    hijoDerecha = nodo;
}
