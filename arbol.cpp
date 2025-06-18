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

Nodo *Arbol::insertar(Biblioteca *nuevaBiblioteca)
{
    raiz = insertarRecursivo(raiz, nuevaBiblioteca);
    return raiz;
}

Nodo *Arbol::insertarRecursivo(Nodo *nodo, Biblioteca *biblio)
{
    if (!nodo)
        nodo = new Nodo(biblio);
    else if (biblio->getCantidadUsuarios() < nodo->getBiblioteca()->getCantidadUsuarios())
        nodo->setHijoIzquierda(insertarRecursivo(nodo->getHijoIzquierda(), biblio));
    else
        nodo->setHijoDerecha(insertarRecursivo(nodo->getHijoDerecha(), biblio));
    return nodo;
}

void Arbol::tratar(Nodo *nodo)
{
    nodo->getBiblioteca()->mostrar();
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

void Arbol::recorreEInsertaEnTabla(Nodo *raiz, TablaHash &tablaH)
{
    if (raiz != nullptr)
    {
        tablaH.insertar(raiz->getBiblioteca()->getCodigo());

        Nodo *hijoIzq = raiz->getHijoIzquierda();
        Nodo *hijoDer = raiz->getHijoDerecha();

        if (hijoIzq != nullptr)
        {
            tablaH.insertar(hijoIzq->getBiblioteca()->getCodigo());
        }

        if (hijoDer != nullptr)
        {
            tablaH.insertar(hijoDer->getBiblioteca()->getCodigo());
        }

        recorreEInsertaEnTabla(hijoIzq, tablaH);
        recorreEInsertaEnTabla(hijoDer, tablaH);
    }
}

Nodo *Arbol::encontrarPadre(string codigoBiblioteca, int cantidadUsuarios)
{
    Nodo *padre = nullptr;
    Nodo *actual = raiz;
    if (!raiz or raiz->getBiblioteca()->getCodigo() == codigoBiblioteca)
        padre = nullptr;
    else
    {
        while (actual != nullptr && padre == nullptr)
        {
            if (actual->getHijoIzquierda() &&
                actual->getHijoIzquierda()->getBiblioteca()->getCantidadUsuarios() == cantidadUsuarios &&
                actual->getHijoIzquierda()->getBiblioteca()->getCodigo() == codigoBiblioteca)
            {
                padre = actual;
            }
            else if (actual->getHijoDerecha() &&
                     actual->getHijoDerecha()->getBiblioteca()->getCantidadUsuarios() == cantidadUsuarios &&
                     actual->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
            {
                padre = actual;
            }
            else
            {
                if (cantidadUsuarios < actual->getBiblioteca()->getCantidadUsuarios())
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
    if (padreNodo == nullptr) // es raiz x lo que no tiene padre
    {
        aux = raiz;
        raiz = nullptr;
    }
    else if (padreNodo->getHijoDerecha() and padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
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

    if (padreNodo == nullptr)
    {
        aux = raiz;
    }
    else if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
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

    if (padreNodo == nullptr)
        raiz = hijoUnico;
    else if (esDerecha)
        padreNodo->setHijoDerecha(hijoUnico);
    else
        padreNodo->setHijoIzquierda(hijoUnico);
    delete aux;
};

Nodo *Arbol::padreMayorDeSubarbol(Nodo *nodo)
{
    Nodo *padre = nodo;
    Nodo *actual = nodo;

    while (actual && actual->getHijoDerecha())
    {
        padre = actual;
        actual = actual->getHijoDerecha();
    }
    return padre;
}

void Arbol::eliminarCaso3(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *nodoAEliminar;

    if (padreNodo == nullptr)
        nodoAEliminar = raiz;
    else if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
        nodoAEliminar = padreNodo->getHijoDerecha();
    else
        nodoAEliminar = padreNodo->getHijoIzquierda();

    // nodo mayor del subárbol izquierdo
    Nodo *padreDelMayor = nodoAEliminar;
    Nodo *mayor = nodoAEliminar->getHijoIzquierda();

    while (mayor->getHijoDerecha() != nullptr)
    {
        padreDelMayor = mayor;
        mayor = mayor->getHijoDerecha();
    }

    // veo si el mayor es hijo directo del nodo a eliminar
    if (padreDelMayor == nodoAEliminar)
        mayor->setHijoDerecha(nodoAEliminar->getHijoDerecha());
    else
    {
        padreDelMayor->setHijoDerecha(mayor->getHijoIzquierda());
        mayor->setHijoIzquierda(nodoAEliminar->getHijoIzquierda());
        mayor->setHijoDerecha(nodoAEliminar->getHijoDerecha());
    }

    // uno al padre del nodo original al nuevo nodo
    if (padreNodo == nullptr)
        raiz = mayor;
    else if (padreNodo->getHijoIzquierda() == nodoAEliminar)
        padreNodo->setHijoIzquierda(mayor);
    else
        padreNodo->setHijoDerecha(mayor);
    delete nodoAEliminar;
}

bool Arbol::borrar(string codigoBiblioteca, int cantidadUsuarios)
{
    bool seBorro = false;
    if (raiz && raiz->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        Nodo *nodoConCodigo = raiz;

        if (!nodoConCodigo->getHijoIzquierda() && !nodoConCodigo->getHijoDerecha())
            eliminarCaso1(nullptr, codigoBiblioteca);
        else if (!nodoConCodigo->getHijoIzquierda() || !nodoConCodigo->getHijoDerecha())
            eliminarCaso2(nullptr, codigoBiblioteca);
        else
            eliminarCaso3(nullptr, codigoBiblioteca);

        cout << "Se elimino con exito del arbol la biblioteca con codigo: " << codigoBiblioteca << " y con la cantidad de usuarios: " << cantidadUsuarios << endl;
        seBorro = true;
    }
    else
    {
        Nodo *padreNodo = encontrarPadre(codigoBiblioteca, cantidadUsuarios);
        if (padreNodo != nullptr)
        {
            Nodo *nodoConCodigo = nullptr;
            if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
                nodoConCodigo = padreNodo->getHijoDerecha();
            else if (padreNodo->getHijoIzquierda() && padreNodo->getHijoIzquierda()->getBiblioteca()->getCodigo() == codigoBiblioteca)
                nodoConCodigo = padreNodo->getHijoIzquierda();

            if (nodoConCodigo != nullptr)
            {
                if (!nodoConCodigo->getHijoIzquierda() && !nodoConCodigo->getHijoDerecha())
                    eliminarCaso1(padreNodo, codigoBiblioteca);
                else if (!nodoConCodigo->getHijoIzquierda() || !nodoConCodigo->getHijoDerecha())
                    eliminarCaso2(padreNodo, codigoBiblioteca);
                else
                    eliminarCaso3(padreNodo, codigoBiblioteca);

                cout << "Se elimino con exito del arbol la biblioteca con codigo: " << codigoBiblioteca << " y con la cantidad de usuarios: " << cantidadUsuarios << endl;
                seBorro = true;
            }
            else
            {
                cout << "No se encontro en el arbol la biblioteca con codigo: " << codigoBiblioteca << " y con la cantidad de usuarios: " << cantidadUsuarios << endl;
            }
        }
        else
        {
            cout << "No se encontro en el arbol la biblioteca con codigo: " << codigoBiblioteca << " y con la cantidad de usuarios: " << cantidadUsuarios << endl;
        }
    }
    return seBorro;
}

void Arbol::buscar(Nodo *nodo, string codigoBiblioteca, int cantidadUsuarios)
{
    if (nodo != NULL)
    {
        if (nodo->getBiblioteca()->getCodigo() == codigoBiblioteca &&
            nodo->getBiblioteca()->getCantidadUsuarios() == cantidadUsuarios)
            nodo->getBiblioteca()->mostrar();
        else if (cantidadUsuarios >= nodo->getBiblioteca()->getCantidadUsuarios())
            buscar(nodo->getHijoDerecha(), codigoBiblioteca, cantidadUsuarios);
        else if (cantidadUsuarios <= nodo->getBiblioteca()->getCantidadUsuarios())
            buscar(nodo->getHijoIzquierda(), codigoBiblioteca, cantidadUsuarios);
    }
    else
        cout << "No se encontro la biblioteca en el arbol" << endl;
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
};