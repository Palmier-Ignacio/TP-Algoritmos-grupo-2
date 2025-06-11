#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "celda.h"        
#include "biblioteca.h"
#include <string>
using namespace std;
class TablaHash
{
private:
    int tamanio;
    Celda* tabla;

    int funcionHash(const string &clave);

public:
    TablaHash(int tamanio);
    ~TablaHash();
    void insertar(string valorBiblio);
    int getTamanio();
    void buscarBiblioteca(string valorBiblio);
    void mostrarBibliotecas();
    int buscarIndiceParaInsertar(const string &clave);
    int buscarIndiceDeClave(const string &clave);

};

#endif
