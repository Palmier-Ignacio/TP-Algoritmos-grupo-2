#include "prestamo.h"
#include <fstream>
#include <sstream>
//include <ctime> puede que nos sirva para la fecha

//---------------------Constructor y Destructor-----------------------------
Prestamo::Prestamo(string codigo_biblioteca, string ISBN, string usuario_id, string fecha_prestamo) {
    this->codigo_biblioteca = codigo_biblioteca;
    this->ISBN = ISBN;
    this->usuario_id = usuario_id; // Preguntar como es el tema
    this->fecha_prestamo = fecha_prestamo; // Formato: "YYYY-MM-DD"
}

Prestamo::~Prestamo() {

}

//---------------------Getters y Setters-----------------------------
void Prestamo::mostrar() {
  

  cout << "Prestamo: Codigo de biblioteca: " << this->codigo_biblioteca << " | ISBN: " << this->ISBN << " | Usuario ID: " 
    << this->usuario_id << " | Fecha del prestamo: " << this->fecha_prestamo << endl;
  

}

string Prestamo::getCodigoBiblioteca() {
  return codigo_biblioteca;
}

string Prestamo::getISBN() {
  return ISBN;
}

string Prestamo::getUsuarioId() {
  return usuario_id;
}

string Prestamo::getFechaPrestamo() {
  return fecha_prestamo;
}

void Prestamo::setCodigoBiblioteca(string nuevoCodigoBiblioteca) {
  codigo_biblioteca = nuevoCodigoBiblioteca;
}

void Prestamo::setISBN(string nuevoISBN) {
  ISBN = nuevoISBN;
}

void Prestamo::setUsuarioId(string nuevoUsuarioId) {
  usuario_id = nuevoUsuarioId;
}

void Prestamo::setFechaPrestamo(string nuevaFechaPrestamo) {
  fecha_prestamo = nuevaFechaPrestamo;
}


//----------------------Metodos requeridos-----------------------------

vector<string> Prestamo::detectarBibliotecasConAltaCargaSemanal(int cantidadDePrestamos){
    return vector<string>();
}

vector<Prestamo> Prestamo::obtenerPrestamosDeUsuarioPorISBN(string ISBN) {
    return vector<Prestamo>();
}
