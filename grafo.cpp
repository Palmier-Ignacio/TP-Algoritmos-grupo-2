#include "grafo.h"
#include "adyacente.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <limits>

using namespace std;

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

Grafo* Grafo::crearDesdeArchivo(const string& nombreArchivo) {
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
void Grafo::floydWarshall() {
    int n = nodos.size();
    matrizDistancias = std::vector<std::vector<double>>(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
    matrizCaminos = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));

    // Inicializar matrizDistancias y matrizCaminos
    for (int i = 0; i < n; ++i) {
        matrizDistancias[i][i] = 0;
        matrizCaminos[i][i] = i;
        NodoGrafo* nodo = nodos[i];
        for (Adyacente* ady : nodo->getAdyacentes()) {
            int j = -1;
            // Buscar índice del nodo destino
            for (int k = 0; k < n; ++k) {
                if (nodos[k] == ady->getDestino()) {
                    j = k;
                    break;
                }
            }
            if (j != -1) {
                matrizDistancias[i][j] = ady->getDistancia();
                matrizCaminos[i][j] = j;
            }
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrizDistancias[i][k] + matrizDistancias[k][j] < matrizDistancias[i][j]) {
                    matrizDistancias[i][j] = matrizDistancias[i][k] + matrizDistancias[k][j];
                    matrizCaminos[i][j] = matrizCaminos[i][k];
                }
            }
        }
    }
}

int Grafo::obtenerIndicePorNombre(const std::string& nombre) {
    for (int i = 0; i < (int)nodos.size(); ++i) {
        if (nodos[i]->getBiblioteca() == nombre) return i;
    }
    return -1; // no encontrado
}

std::vector<std::string> Grafo::obtenerCaminoMinimo(int indiceOrigen, int indiceDestino) {
    std::vector<std::string> camino;
    if (matrizCaminos.empty() || indiceOrigen == -1 || indiceDestino == -1) return camino;

    int actual = indiceOrigen;
    camino.push_back(nodos[actual]->getBiblioteca());

    while (actual != indiceDestino) {
        actual = matrizCaminos[actual][indiceDestino];
        if (actual == -1) return {}; // no hay camino
        camino.push_back(nodos[actual]->getBiblioteca());
    }
    return camino;
}
double Grafo::obtenerDistancia(int indiceOrigen, int indiceDestino) {
    if (indiceOrigen < 0 || indiceOrigen >= (int)matrizDistancias.size()) return std::numeric_limits<double>::infinity();
    if (indiceDestino < 0 || indiceDestino >= (int)matrizDistancias.size()) return std::numeric_limits<double>::infinity();
    return matrizDistancias[indiceOrigen][indiceDestino];
}

