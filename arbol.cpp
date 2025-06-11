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
    cout << "Se anadio con exito la biblioteca";
    nuevaBiblioteca->mostrar();
}

Nodo *Arbol::insertarRecursivo(Nodo *nodo, Biblioteca *biblio)
{
    if (!nodo)
    {
        nodo = new Nodo(biblio);
    }
    else if (biblio->getCodigo() < nodo->getBiblioteca()->getCodigo())
    {
        nodo->setHijoIzquierda(insertarRecursivo(nodo->getHijoIzquierda(), biblio));
    }
    else
    {
        nodo->setHijoIzquierda(insertarRecursivo(nodo->getHijoDerecha(), biblio));
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

void Arbol::eliminarCaso1(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *aux;
    if (padreNodo->getHijoDerecha() and padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        aux = padreNodo->getHijoDerecha();
        padreNodo->setHijoDerecha(nullptr);
    }
    else
    {
        aux = padreNodo->getHijoIzquierda();
        padreNodo->setHijoIzquierda(nullptr);
    }
    delete aux;
};

void Arbol::eliminarCaso2(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *aux;
    bool esDerecha;

    if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        aux = padreNodo->getHijoDerecha();
        esDerecha = true;
    }
    else
    {
        aux = padreNodo->getHijoIzquierda();
        esDerecha = false;
    }

    Nodo *hijoUnico = aux->getHijoIzquierda() ? aux->getHijoIzquierda() : aux->getHijoDerecha();

    if (esDerecha)
        padreNodo->setHijoDerecha(hijoUnico);
    else
        padreNodo->setHijoIzquierda(hijoUnico);

    delete aux;
};

Nodo *Arbol::padreMayorDeSubarbol(Nodo *nodo)
{
    Nodo *padre = nodo;
    Nodo *actual = nodo;

    if (!actual)
    {
        while (actual->getHijoDerecha())
        {
            padre = actual;
            actual = actual->getHijoDerecha();
        }
    }

    return padre;
}

void Arbol::eliminarCaso3(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *aux;

    // Obtener puntero al nodo que contiene el código a eliminar
    if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        aux = padreNodo->getHijoDerecha();
    }
    else
    {
        aux = padreNodo->getHijoIzquierda();
    }

    // Paso 1: Obtener padre del mayor de los menores
    Nodo *padreMayorMenores = padreMayorDeSubarbol(aux->getHijoIzquierda());

    Nodo *mayorMenor;

    // Caso especial: el hijo izquierdo de aux es el mayor de los menores
    if (padreMayorMenores == aux)
    {
        mayorMenor = aux->getHijoIzquierda();
    }
    else
    {
        mayorMenor = padreMayorMenores->getHijoDerecha();
    }

    // Paso 2: reconectar el padre del nodo que contiene x con el nuevo nodo
    if (padreNodo->getHijoDerecha() == aux)
    {
        padreNodo->setHijoDerecha(mayorMenor);
    }
    else
    {
        padreNodo->setHijoIzquierda(mayorMenor);
    }

    // Paso 3: reconectar los hijos del nodo original (aux) al nuevo nodo
    mayorMenor->setHijoIzquierda(aux->getHijoIzquierda());
    mayorMenor->setHijoDerecha(aux->getHijoDerecha());

    // Paso 4: eliminar el nodo mayor de los menores desde su antigua posición
    if (mayorMenor->getHijoIzquierda() == nullptr && mayorMenor->getHijoDerecha() == nullptr)
    {
        eliminarCaso1(padreMayorMenores, mayorMenor->getBiblioteca()->getCodigo());
    }
    else
    {
        eliminarCaso2(padreMayorMenores, mayorMenor->getBiblioteca()->getCodigo());
    }

    // Paso 5: eliminar el nodo original
    delete aux;
};

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

void Arbol::buscar(Nodo *nodo, string codigoBiblioteca)
{
    if (nodo != NULL)
    {
        if (nodo->getBiblioteca()->getCodigo() == codigoBiblioteca)
        {
            nodo->getBiblioteca()->mostrar();
        }
        else if (codigoBiblioteca > nodo->getBiblioteca()->getCodigo())
        {
            buscar(nodo->getHijoDerecha(), codigoBiblioteca);
        }
        else if (codigoBiblioteca < nodo->getBiblioteca()->getCodigo())
        {
            buscar(nodo->getHijoIzquierda(), codigoBiblioteca);
        }
        else
        {
            cout << "No se encontro la biblioteca";
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
