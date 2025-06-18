#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include "nodo.h"
#include "tablaHash.h"
#include "biblioteca.h"

class Arbol
{
private:
    Nodo *raiz;

    Nodo *insertarRecursivo(Nodo *nodo, Biblioteca *biblio);

public:
    Arbol();

    Arbol(Biblioteca *biblio);

    Nodo *getRaiz();

    Nodo * insertar(Biblioteca *nuevaBiblioteca);

    void tratar(Nodo *nodo);

    void liberar(Nodo *nodo);

    void inorden(Nodo *raiz);

    void recorreEInsertaEnTabla(Nodo *raiz, TablaHash& tablaH);

    Nodo *encontrarPadre(string codigoBiblioteca, int cantidadUsuarios);

    bool borrar(string codigoBiblioteca, int cantidadUsuarios);

    Nodo *padreMayorDeSubarbol(Nodo *nodo);

    void eliminarCaso1(Nodo *nodo, string codigoBiblioteca);

    void eliminarCaso2(Nodo *nodo, string codigoBiblioteca);

    void eliminarCaso3(Nodo *nodo, string codigoBiblioteca);

    void buscar(Nodo *nodo, string codigoBiblioteca, int cantidadUsuarios);
};

#endif
