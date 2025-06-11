#include "grafo.h"
#include "adyacente.h"
#include <sstream>

void Grafo::addNodo(NodoGrafo* nodo) {
    nodos.push_back(nodo);
}

vector<NodoGrafo*>& Grafo::getNodos() {
    return nodos;
}

string Grafo::toString() {
    ostringstream oss;
    oss << "Grafo [\n";

    for (NodoGrafo* nodo : nodos) {
        oss << " Biblioteca: " << nodo->getBiblioteca() << "\n";
        oss << "  Adyacentes:\n";

        for (Adyacente* ady : nodo->getAdyacentes()) {
            oss << "    -> " << ady->getDestino()->getBiblioteca() 
                << " (distancia: " << ady->getDistancia() << ")\n";
        }
        oss << "\n";
    }

    oss << "]";
    return oss.str();
}


Grafo::~Grafo() {
    for (NodoGrafo* nodo : nodos) {
        delete nodo;
    }
}
