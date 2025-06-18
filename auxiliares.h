#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "arbol.h"
#include "prestamo.h"
#include "biblioteca.h"
#include <vector>
#include <string>

using namespace std;

int cargarBibliotecas(string nombreArchivo,Arbol& arbol);
void cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos);
int totalPrestamosDeBiblioteca_Durante_(vector<Prestamo*> prestamos, string codigo, string fechaInicio, string fechaFin);
vector<string> detectarBibliotecasConAltaCargaSemanal(vector<Prestamo*> prestamos, int cantidadDePrestamos, string fechaInicio, string fechaFin);
//buscar todos los prestamos de un usuario por codigo ISBN ?
// suponemos que la funcionalidad pide que se devuelva los prestamos de un usuario del mismo libro?
// como buscamos los prestamos de un solo usuario si nos pide que los busquemos por ISBN que es el codigo del libro?
//preguntar al profe
vector<Prestamo> obtenerPrestamosDeUsuarioPorISBN(vector<Prestamo*> prestamos, string ISBN);

#endif
