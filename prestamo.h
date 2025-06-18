#ifndef PRESTAMO_H_INCLUDED
#define PRESTAMO_H_INCLUDED
#include <iostream>
#include <vector>
#include "biblioteca.h"
using namespace std;

class Prestamo {
private:
  // atributos
  string codigo_biblioteca;
  string ISBN; 
  string usuario_id; // ??? ver esto
  string fecha_prestamo;

public:
  // constructor
  // pos: crea un prestamo con sus atributos
  Prestamo(string codigo_biblioteca, string ISBN, string usuario_id, string fecha_prestamo);

  // pos: libera la memoria
  virtual ~Prestamo();

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
  vector<string> detectarBibliotecasConAltaCargaSemanal(int cantidadDePrestamos);

  // pos: devuelve una lista de todos los prestamos de un usuario
  vector<Prestamo> obtenerPrestamosDeUsuarioPorISBN(string ISBN);

  
};

#endif