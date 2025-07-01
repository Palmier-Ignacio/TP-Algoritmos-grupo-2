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
        nodo = new Nodo(biblio); // caso base: crea un nuevo nodo si esta vacooio
    else if (biblio->getCantidadUsuarios() < nodo->getBiblioteca()->getCantidadUsuarios())
        nodo->setHijoIzquierda(insertarRecursivo(nodo->getHijoIzquierda(), biblio)); // inserta a la izq si tiene menos usuarios
    else
        nodo->setHijoDerecha(insertarRecursivo(nodo->getHijoDerecha(), biblio)); // inserta a la der si tiene mas usuarios
    return nodo;
}

// muestra los datos de la biblioteca guardada por el nodo por terminal
void Arbol::tratar(Nodo *nodo)
{
    nodo->getBiblioteca()->mostrar();
}

// muestra las bibliotecas de menor a mayor segun la cantidad de usuarios. O(n)
void Arbol::inorden(Nodo *raiz)
{
    if (raiz != nullptr)
    {
        inorden(raiz->getHijoIzquierda());
        tratar(raiz);
        inorden(raiz->getHijoDerecha());
    }
}

// recorre arbol e inserta en tablaHash los codigos de las bibliotecas guardadas O(n)
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

// devuelve el nodo padre de una biblioteca guardada solicitada, sirve para la funcion borrar
Nodo *Arbol::encontrarPadre(string codigoBiblioteca, int cantidadUsuarios)
{
    Nodo *padre = nullptr;
    Nodo *actual = raiz;
    // si  no hay raiz o la raiz es la biblioteca a la que queremos encontrar su nodo padre, es que no hay padre
    if (!raiz or raiz->getBiblioteca()->getCodigo() == codigoBiblioteca)
        padre = nullptr;
    else
    { // si se encuentra al padre o el actual esta vacio para
        while (actual != nullptr && padre == nullptr)
        {
            // si el actual tiene de hijo izquierda a la biblioteca buscada
            if (actual->getHijoIzquierda() &&
                actual->getHijoIzquierda()->getBiblioteca()->getCantidadUsuarios() == cantidadUsuarios &&
                actual->getHijoIzquierda()->getBiblioteca()->getCodigo() == codigoBiblioteca)
            {
                padre = actual;
            }
            // si el actual tiene de hijo derecha a la biblioteca buscada
            else if (actual->getHijoDerecha() &&
                     actual->getHijoDerecha()->getBiblioteca()->getCantidadUsuarios() == cantidadUsuarios &&
                     actual->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
            {
                padre = actual;
            }
            else
            // el actual no es padre, ve si tiene que buscar hacia la derecha o izquierda segun la cantidad de usuarios
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
// elimina un nodo que no tiene hijos
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
    delete aux; // liberamos memoria
};

// el nodo a eliminar tiene solo un hijo
void Arbol::eliminarCaso2(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *aux;
    bool esDerecha;

    // si no hay padre, es raiz el nodo a eliminar
    if (padreNodo == nullptr)
    {
        aux = raiz;
    }
    // el nodo a eliminar es el derecho
    else if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        aux = padreNodo->getHijoDerecha();
        esDerecha = true;
    }
    // el nodo a eliminar es el izquierdo
    else
    {
        aux = padreNodo->getHijoIzquierda();
        esDerecha = false;
    }

    // obtenemos al hijo del nodo a eliminar
    Nodo *hijoUnico = aux->getHijoIzquierda() ? aux->getHijoIzquierda() : aux->getHijoDerecha();

    // en el caso de que se elimine la raiz, se setea como raiz al hijo, en los otros casos, se conecta al padre con el hijo del nodo que eliminamos
    if (padreNodo == nullptr)
        raiz = hijoUnico;
    else if (esDerecha)
        padreNodo->setHijoDerecha(hijoUnico);
    else
        padreNodo->setHijoIzquierda(hijoUnico);
    delete aux; // liberamos memoria
};

Nodo *Arbol::padreMayorDeSubarbol(Nodo *nodo)
{ // sirve para el caso eliminar 3, busca el padre del mayor
    Nodo *padre = nodo;
    Nodo *actual = nodo;

    while (actual && actual->getHijoDerecha())
    {
        padre = actual;
        actual = actual->getHijoDerecha();
    }
    return padre;
}

// si el nodo a eliminar tiene dos hijos
void Arbol::eliminarCaso3(Nodo *padreNodo, string codigoBiblioteca)
{
    Nodo *nodoAEliminar;
    // se indica cual es el nodo a eliminar
    if (padreNodo == nullptr)
        nodoAEliminar = raiz;
    else if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
        nodoAEliminar = padreNodo->getHijoDerecha();
    else
        nodoAEliminar = padreNodo->getHijoIzquierda();

    // se busca el nodo mayor del subárbol izquierdo
    Nodo *padreDelMayor = nodoAEliminar;
    Nodo *mayor = nodoAEliminar->getHijoIzquierda();

    while (mayor->getHijoDerecha() != nullptr)
    {
        padreDelMayor = mayor;
        mayor = mayor->getHijoDerecha(); // recorre hacia la derecha buscando el mayor
    }

    // ajusta punteros segun si el mayor es hijo directo o no del nodo a eliminar
    if (padreDelMayor == nodoAEliminar)
        // el mayor es hijo izquierdo directo del nodo a eliminar
        mayor->setHijoDerecha(nodoAEliminar->getHijoDerecha());
    else
    {
        // el mayor tiene un padre mas arriba, o sea no es hijo directo
        padreDelMayor->setHijoDerecha(mayor->getHijoIzquierda());   // reconecta el hijo izquierdo del mayor al padre del mayor
        mayor->setHijoIzquierda(nodoAEliminar->getHijoIzquierda()); // setea hijos del nodo eliminado al mayor
        mayor->setHijoDerecha(nodoAEliminar->getHijoDerecha());
    }

    // uno al padre del nodo original al nuevo nodo
    if (padreNodo == nullptr)
        raiz = mayor; // si eliminamos la raiz
    else if (padreNodo->getHijoIzquierda() == nodoAEliminar)
        padreNodo->setHijoIzquierda(mayor);
    else
        padreNodo->setHijoDerecha(mayor);
    delete nodoAEliminar; // borro memoria del nodo eliminado
}

bool Arbol::borrar(string codigoBiblioteca, int cantidadUsuarios)
{
    bool seBorro = false;
    // si la raiz es la biblioteca que queremos eliminar
    if (raiz && raiz->getBiblioteca()->getCodigo() == codigoBiblioteca)
    {
        Nodo *nodoConCodigo = raiz;
        // si no tiene hijos el nodo
        if (!nodoConCodigo->getHijoIzquierda() && !nodoConCodigo->getHijoDerecha())
            eliminarCaso1(nullptr, codigoBiblioteca);
        // si tiene un solo hijo
        else if (!nodoConCodigo->getHijoIzquierda() || !nodoConCodigo->getHijoDerecha())
            eliminarCaso2(nullptr, codigoBiblioteca);
        // si tiene dos hijos
        else
            eliminarCaso3(nullptr, codigoBiblioteca);

        cout << "Se elimino con exito del arbol la biblioteca con codigo: " << codigoBiblioteca << " y con la cantidad de usuarios: " << cantidadUsuarios << endl;
        seBorro = true;
    }
    else
    {
        // si no es raiz el nodo a eliminar. Buscamos al padre del nodo
        Nodo *padreNodo = encontrarPadre(codigoBiblioteca, cantidadUsuarios);
        if (padreNodo != nullptr)
        {
            Nodo *nodoConCodigo = nullptr;
            // buscamos cual nodo hijo del padre es el que queremos borrar
            if (padreNodo->getHijoDerecha() && padreNodo->getHijoDerecha()->getBiblioteca()->getCodigo() == codigoBiblioteca)
                nodoConCodigo = padreNodo->getHijoDerecha();
            else if (padreNodo->getHijoIzquierda() && padreNodo->getHijoIzquierda()->getBiblioteca()->getCodigo() == codigoBiblioteca)
                nodoConCodigo = padreNodo->getHijoIzquierda();

            if (nodoConCodigo != nullptr)
            {
                // si el nodo a eliminar no tiene hijos
                if (!nodoConCodigo->getHijoIzquierda() && !nodoConCodigo->getHijoDerecha())
                    eliminarCaso1(padreNodo, codigoBiblioteca);
                // si el nodo a eliminar  tiene un solo hijo
                else if (!nodoConCodigo->getHijoIzquierda() || !nodoConCodigo->getHijoDerecha())
                    eliminarCaso2(padreNodo, codigoBiblioteca);
                // si el nodo a eliminar  tiene dos hijos
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
    // Busca a la biblioteca recursivamente segun el codigo y su cantidad de usuarios para ir moviendose de izq a der. O( log n)
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
    // pasa recursivamente por todo el arbol eliminando cada nodo y  biblioteca para liberar memoria. O(n)
    if (nodo)
    {
        liberar(nodo->getHijoIzquierda());
        liberar(nodo->getHijoDerecha());
        delete nodo->getBiblioteca();
        delete nodo;
    }
};