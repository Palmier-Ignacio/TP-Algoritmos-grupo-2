#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include "nodo.h"
#include "tablaHash.h"
#include <stack>

class Arbol
{
private:
    Nodo *raiz;

    Nodo *insertarRecursivo(Nodo *nodo, Biblioteca *biblio);

public:
    Arbol();

    Arbol(Biblioteca *biblio);

    Nodo *getRaiz();

    void insertar(Biblioteca *nuevaBiblioteca);

    void tratar(Nodo *nodo);

    int cantidadNodos(Nodo *nodo);

    int altura(Nodo *nodo);

    void liberar(Nodo *nodo);

    void inorden(Nodo *raiz);

    void recorreEInsertaEnTabla(Nodo *raiz, TablaHash& tablaH);

    Nodo *encontrarPadre(string codigoBiblioteca);

    void borrar(string codigoBiblioteca);

    Nodo *padreMayorDeSubarbol(Nodo *nodo);

    void eliminarCaso1(Nodo *nodo, string codigoBiblioteca);

    void eliminarCaso2(Nodo *nodo, string codigoBiblioteca);

    void eliminarCaso3(Nodo *nodo, string codigoBiblioteca);

    void buscar(Nodo *nodo, string codigoBiblioteca);
};

#endif
