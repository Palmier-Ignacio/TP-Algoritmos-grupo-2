#include "crearGrafo.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>

#include "nodoGrafo.h"
#include "adyacente.h"

using namespace std;

Grafo* crearGrafoDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    unordered_map<string, NodoGrafo*> mapaNodos;
    Grafo* grafo = new Grafo();

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string origenStr, destinoStr;
        double distancia;

        if (!(iss >> origenStr >> destinoStr >> distancia)) {
            cerr << "Error leyendo linea: " << linea << endl;
            continue;
        }

        NodoGrafo* origen = nullptr;
        auto itOrigen = mapaNodos.find(origenStr);
        if (itOrigen == mapaNodos.end()) {
            origen = new NodoGrafo(origenStr);
            mapaNodos[origenStr] = origen;
            grafo->addNodo(origen);
        } else {
            origen = itOrigen->second;
        }

        NodoGrafo* destino = nullptr;
        auto itDestino = mapaNodos.find(destinoStr);
        if (itDestino == mapaNodos.end()) {
            destino = new NodoGrafo(destinoStr);
            mapaNodos[destinoStr] = destino;
            grafo->addNodo(destino);
        } else {
            destino = itDestino->second;
        }

        Adyacente* ady = new Adyacente(origen, destino, distancia);
        origen->addAdyacente(ady);
    }

    archivo.close();
    return grafo;
}
