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

    // pos: aplica la función hash a una clave dada
    int funcionHash(const string &clave);

public:
    // pos: cre una tabla hash con un tamaño determinado
    TablaHash(int tamanio);

    // pos: libera la memoria reservada para la tabla.
    ~TablaHash();

    // pos: inserta el codigo de una biblioteca en la tabla.
    void insertar(string valorBiblio);

    // pos: elimina el codigo de una biblioteca en la tabla.
    void eliminar(const string &clave);

    // pos: retorna el tamanio de la tabla.
    int getTamanio();

    // pos: muestra por pantalla la biblioteca si se encontró o un mensaje de no se encontro.
    void buscarBiblioteca(string valorBiblio);

    // pos: muestra por pantalla todas las bibliotecas en la tabla según el orden en que se guardaron luego de aplicar la funcion hash.
    void mostrarBibliotecas();

    // pos: devuelve el primer indice encontrado o un mensaje si no lo hizo.
    int buscarIndiceParaInsertar(const string &clave);

    // pos: devuelve el indice de la clave dada o un mensaje si no lo hizo.
    int buscarIndiceDeClave(const string &clave);

};

#endif
