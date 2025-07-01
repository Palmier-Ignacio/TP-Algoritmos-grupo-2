#ifndef PRESTAMO_H_INCLUDED
#define PRESTAMO_H_INCLUDED
#include <iostream>
#include <vector>
#include "biblioteca.h"
#include <set>

using namespace std;

class Prestamo
{
private:
  // atributos
  string codigo_biblioteca;
  string ISBN;
  string usuario_id;
  string fecha_prestamo;

public:
  // constructor
  // pos: crea un prestamo con sus atributos
  Prestamo(string codigo_biblioteca, string ISBN, string usuario_id, string fecha_prestamo);
  // pos: imprime los datos del prestamo
  void mostrar();
  // pos: imprime el codigo de la biblioteca
  string getCodigoBiblioteca();
  // pos: imprime el ISBN del libro
  string getISBN();
  // pos: imprime el id del usuario
  string getUsuarioId();
  // pos: imprime la fecha del prestamo
  string getFechaPrestamo();
  // pos: setea el codigo de la biblioteca pasado por parametro
  void setCodigoBiblioteca(string nuevoCodigoBiblioteca);
  // pos: setea el ISBN del libro pasado por parametro
  void setISBN(string nuevoISBN);
  // pos: setea el id del usuario pasado por parametro
  void setUsuarioId(string nuevoUsuarioId);
  // pos: setea la fecha del prestamo pasado por parametro
  void setFechaPrestamo(string nuevaFechaPrestamo);
  // pos: devuelve una lista de los codigos de bibliotecas con mas de "X" carga de prestamos en una semana
  static vector<string> detectarBibliotecasConAltaCargaSemanal(vector<Prestamo *> prestamos, int cantidadDePrestamos);
  // pos: devuelve una lista de todos los prestamos de un usuario
  static vector<Prestamo> obtenerPrestamosDeUsuarioPorISBN(vector<Prestamo *> prestamos, string codigoUsuario);
  // pos: devuelve la cantidad de prestamos de un un libro durante las fechas recibidas
  static int totalPrestamosDeBiblioteca_Durante_(vector<Prestamo *> prestamos, string codigo, string fechaInicio, string fechaFin);
  // pos: carga los prestamos leidos en un archivo de texto a un vector
  static void cargarPrestamos(string nombreArchivo, vector<Prestamo *> &prestamos);
};
#endif