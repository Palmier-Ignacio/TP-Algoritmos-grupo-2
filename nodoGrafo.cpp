#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "nodoGrafo.h"
#include "adyacente.h"

NodoGrafo::NodoGrafo(const string& biblioteca) {
    this->biblioteca = biblioteca;
}

string NodoGrafo::getBiblioteca() {
    return biblioteca;
}

void NodoGrafo::setBiblioteca(const string& nuevaBiblioteca) {
    biblioteca = nuevaBiblioteca;
}

vector<Adyacente*>& NodoGrafo::getAdyacentes() {
    return adyacentes;
}

void NodoGrafo::addAdyacente(Adyacente* adyacente) {
    adyacentes.push_back(adyacente);
}

NodoGrafo::~NodoGrafo() {
    // Liberamos la memoria de cada adyacente
    for (Adyacente* ady : adyacentes) {
        delete ady;
    }
}