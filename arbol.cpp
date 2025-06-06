#include <iostream>
#include "arbol.h"

using namespace std;

Arbol::Arbol(Biblioteca *biblio)
{
    raiz = new Nodo(biblio);
}

Arbol::Arbol()
{
    raiz = nullptr;
}

Nodo *Arbol::getRaiz()
{
    return raiz;
}

void Arbol::insertar(Biblioteca *nuevaBiblioteca)
{
    raiz = insertarRecursivo(raiz, nuevaBiblioteca);
}

Nodo *Arbol::insertarRecursivo(Nodo *nodo, Biblioteca *biblio)
{
    if (!nodo)
    {
        nodo = new Nodo(biblio);
    }
    else if (biblio->getCodigo() < nodo->getBiblioteca()->getCodigo())
    {
        insertarRecursivo(nodo->getHijoIzquierda(), biblio);
    }
    else
    {
        insertarRecursivo(nodo->getHijoDerecha(), biblio);
    }
    return nodo;
}

void Arbol::tratar(Nodo *nodo)
{
    nodo->getBiblioteca()->mostrar();
}

int Arbol::cantidadNodos(Nodo *nodo)
// La complejidad es O(n) porque pasa por todos los nodos que tiene el arbol
{
    if (nodo == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + cantidadNodos(nodo->getHijoIzquierda()) + cantidadNodos(nodo->getHijoDerecha());
    }
}

int Arbol::altura(Nodo *nodo)
// La complejidad es O(n) porque pasapor todos los nodos que tiene el arbol
{
    if (nodo == nullptr)
    {
        return 0;
    }
    else
    {
        int alturaIzq = altura(nodo->getHijoIzquierda());
        int alturaDer = altura(nodo->getHijoDerecha());
        return 1 + max(alturaIzq, alturaDer);
    }
}

void Arbol::inorden(Nodo *raiz)
{
    if (raiz != nullptr)
    {
        inorden(raiz->getHijoIzquierda());
        tratar(raiz);
        inorden(raiz->getHijoDerecha());
    }
}

Nodo *Arbol::encontrarPadre(string codigoBiblioteca)
{
    Nodo *padre = nullptr;
    Nodo *actual = raiz;
    if (!raiz or raiz->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        padre = nullptr;
    }
    else
    {
        while (actual != nullptr and padre == nullptr)
        {
            if ((actual->getHijoIzquierda() && actual->getHijoIzquierda()->getBiblioteca()->getCodigo() == codigoBiblioteca) ||
                (actual->getHijoDerecha() && actual->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca))
            {
                padre = actual;
            }
            else
            {
                if (codigoBiblioteca < actual->getBiblioteca()->getCodigo())
                    actual = actual->getHijoIzquierda();
                else
                    actual = actual->getHijoDerecha();
            }
        }
    }

    return padre;
}

void Arbol::eliminarCaso1(Nodo *nodo, string codigoBiblioteca) {
    Nodo *aux = nodo;
};
void Arbol::eliminarCaso2(Nodo *nodo, string codigoBiblioteca) {};
void Arbol::eliminarCaso3(Nodo *nodo, string codigoBiblioteca) {};

void Arbol::borrar(string codigoBiblioteca)
{
    Nodo *padreNodo = encontrarPadre(codigoBiblioteca);
    if (padreNodo != nullptr)
    {
        Nodo *nodoConCodigo = nullptr;
        if (padreNodo->getHijoDerecha() and padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
        {
            nodoConCodigo = padreNodo->getHijoDerecha();
        }
        else
        {
            nodoConCodigo = padreNodo->getHijoIzquierda();
        }

        if (nodoConCodigo->getHijoIzquierda() == nullptr and nodoConCodigo->getHijoDerecha() == nullptr)
        {
            eliminarCaso1(padreNodo, codigoBiblioteca);
        }
        else if (nodoConCodigo->getHijoIzquierda() == nullptr or nodoConCodigo->getHijoDerecha() == nullptr)
        {
            eliminarCaso2(padreNodo, codigoBiblioteca);
        }
        else
        {
            eliminarCaso3(padreNodo, codigoBiblioteca);
        }
    }
}

void Arbol::liberar(Nodo *nodo)
{
    if (nodo)
    {
        liberar(nodo->getHijoIzquierda());
        liberar(nodo->getHijoDerecha());
        delete nodo->getBiblioteca();
        delete nodo;
    }
}

;
