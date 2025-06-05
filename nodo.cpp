#include <iostream>
#include "biblioteca.h"
using namespace std;

class Nodo {
private:
    Biblioteca *biblioteca;
    Nodo *hijoIzquierda;
    Nodo *hijoDerecha;

public:
    Nodo(int valor) {
        this->biblioteca = biblioteca;
        this->hijoIzquierda = nullptr;
        this->hijoDerecha = nullptr;
    }

    Biblioteca* getBiblioteca() {
        return biblioteca;
    }

    Nodo* getHijoIzquierda() {
        return hijoIzquierda;
    }

    Nodo* getHijoDerecha() {
        return hijoDerecha;
    }

    void setHijoIzquierda(Nodo* nodo) {
        hijoIzquierda = nodo;
    }

    void setHijoDerecha(Nodo* nodo) {
        hijoDerecha = nodo;
    }
};
