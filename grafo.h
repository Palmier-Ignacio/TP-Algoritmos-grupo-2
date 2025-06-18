#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include "nodoGrafo.h" 

// Forward declaration para evitar inclusión circular
class Adyacente;

class Grafo {
private:
    std::vector<std::vector<double>> matrizDistancias;
    std::vector<std::vector<int>> matrizCaminos; 
    std::vector<NodoGrafo*> nodos;

public:
    double obtenerDistancia(int indiceOrigen, int indiceDestino);
    void floydWarshall();
    std::vector<std::string> obtenerCaminoMinimo(int indiceOrigen, int indiceDestino);
    int obtenerIndicePorNombre(const std::string& nombre);
    void addNodo(NodoGrafo* nodo);
    std::vector<NodoGrafo*>& getNodos();
    std::string toString();
    ~Grafo();

    // Método estático para crear un grafo desde archivo
    static Grafo* crearDesdeArchivo(const std::string& nombreArchivo);
};

#endif
