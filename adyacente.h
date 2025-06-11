#ifndef ADYACENTE_H
#define ADYACENTE_H

#include <iostream>
#include <memory>
#include <string>
#include "nodoGrafo.h"

using namespace std;

// Forward declaration para evitar inclusión circular
class NodoGrafo;

class Adyacente {
private:
    NodoGrafo* origen;
    NodoGrafo* destino;
    double distancia;

public:
    Adyacente(NodoGrafo* origen, NodoGrafo* destino, double distancia);

    NodoGrafo* getOrigen();
    NodoGrafo* getDestino();
    double getDistancia();

    void setOrigen(NodoGrafo* nuevoOrigen);
    void setDestino(NodoGrafo* nuevoDestino);
    void setDistancia(double nuevaDistancia);

    string toString();
};

#endif