#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "tablaHash.h"
#include "prestamo.h"
#include <vector>
#include <string>

using namespace std;

int cargarBibliotecas(string nombreArchivo, vector<Biblioteca*>& biblioteca);
int cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos);

#endif
