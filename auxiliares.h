#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "arbol.h"
#include "prestamo.h"
#include "biblioteca.h"
#include <vector>
#include <string>

using namespace std;

int cargarBibliotecas(string nombreArchivo,Arbol& arbol);
int cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos);

#endif
