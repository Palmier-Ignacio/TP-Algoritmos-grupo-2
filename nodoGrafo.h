#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>


using namespace std;
// Forward declaration para evitar inclusión circular
class Adyacente;

class NodoGrafo {
private:
    string biblioteca;
    vector<Adyacente*> adyacentes;

public:
    NodoGrafo(const string& biblioteca);

    string getBiblioteca();
    void setBiblioteca(const string& nuevaBiblioteca);

    vector<Adyacente*>& getAdyacentes();
    void addAdyacente(Adyacente* adyacente);

    ~NodoGrafo();  // Para liberar memoria
};

#endif