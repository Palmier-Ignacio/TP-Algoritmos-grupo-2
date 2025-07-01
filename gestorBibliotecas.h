#ifndef GESTORBIBLIOTECAS_H
#define GESTORBIBLIOTECAS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>
#include "biblioteca.h"
#include "auxiliares.h"
#include "tablaHash.h"
#include "arbol.h"
#include <sstream>
#include "grafo.h"
#include <limits>

class GestorBibliotecas {
private:
    Arbol arbolBibliotecas;
    TablaHash tablaBiblioteca;
    Grafo *grafo;
    std::vector<Prestamo *> prestamos;

    void mostrarMenu();
    void opcionCargarBiblioteca();
    void opcionBuscarBiblioteca();
    void opcionEliminarBiblioteca();
    void opcionMostrarBibliotecas();
    void opcionCalcularDistancia();
    void opcionTotalPrestamosPeriodo();
    void opcionAltaCargaSemanal();
    void opcionPrestamosPorISBN();
    void opcionMostrarTablaHash();

public:
    GestorBibliotecas();
    ~GestorBibliotecas();
    void ejecutar();
};

#endif
