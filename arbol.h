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
    // pos: crea un arbol vacio
    Arbol();

    // pos: crea un arbol con un nodo raiz
    Arbol(Biblioteca *biblio);

    // pos: devuelve la raiz del arbol
    Nodo *getRaiz();

    // pos: inserta una biblioteca en un nodo del arbol
    Nodo *insertar(Biblioteca *nuevaBiblioteca);

    // pos: imprime los datos de la biblioteca almacenada en un nodo
    void tratar(Nodo *nodo);

    // pos libera memoria borrando todos los nodos del arbol y las bibliotecas que estaban almacenadas
    void liberar(Nodo *nodo);

    // pos imprime por pantalla todas las bibliotecas ordenadas de menor a mayor segun la cantidad de usuarios
    void inorden(Nodo *raiz);

    // pos: inserta los codigos de cada biblioteca guardada en el arbol en una tabla hash
    void recorreEInsertaEnTabla(Nodo *raiz, TablaHash &tablaH);

    // pos: devuelve el nodo padre de un nodo solicitado
    Nodo *encontrarPadre(string codigoBiblioteca, int cantidadUsuarios);

    // borra el nodo solicitado del arbol y devuelve un bool para indicar si fue borrado
    bool borrar(string codigoBiblioteca, int cantidadUsuarios);

    // pos: devuelve el nodo padre mayor del subarbol
    Nodo *padreMayorDeSubarbol(Nodo *nodo);

    // pos: elimina el nodo solicitado teniendo en cuenta que no tenga hijos
    void eliminarCaso1(Nodo *nodo, string codigoBiblioteca);

    // pos: elimina el nodo solicitado teniendo en cuenta si tiene un hijo
    void eliminarCaso2(Nodo *nodo, string codigoBiblioteca);

    // pos: elimina el nodo solicitado teniendo en cuenta si tiene dos hijos
    void eliminarCaso3(Nodo *nodo, string codigoBiblioteca);

    // pos: imprime por pantalla la biblioteca solicitada
    void buscar(Nodo *nodo, string codigoBiblioteca, int cantidadUsuarios);
};

#endif
