#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include "nodoGrafo.h" 

using namespace std;
// Forward declaration para evitar inclusión circular
class Adyacente;

class Grafo {
private:
    vector<NodoGrafo*> nodos;

public:
    void addNodo(NodoGrafo* nodo);
    
    vector<NodoGrafo*>& getNodos();

    string toString();

    ~Grafo(); 
};

#endif
