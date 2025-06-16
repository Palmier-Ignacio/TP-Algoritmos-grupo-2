#include "adyacente.h"
#include "nodoGrafo.h"
#include <string>
#include <iostream>


Adyacente::Adyacente(NodoGrafo* origen, NodoGrafo* destino, double distancia) {
    this->origen = origen;
    this->destino = destino;
    this->distancia = distancia;
}

NodoGrafo* Adyacente::getOrigen() {
    return origen;
}

NodoGrafo* Adyacente::getDestino() {
    return destino;
}

double Adyacente::getDistancia() {
    return distancia;
}

void Adyacente::setOrigen(NodoGrafo* nuevoOrigen) {
    origen = nuevoOrigen;
}

void Adyacente::setDestino(NodoGrafo* nuevoDestino) {
    destino = nuevoDestino;
}

void Adyacente::setDistancia(double nuevaDistancia) {
    distancia = nuevaDistancia;
}

string Adyacente::toString() {
    return "Adyacente [origen=" + origen->getBiblioteca() +
           ", destino=" + destino->getBiblioteca() +
           ", distancia=" + to_string(distancia) + "]";
}
