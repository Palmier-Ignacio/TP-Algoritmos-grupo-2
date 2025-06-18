#include "prestamo.h"
#include <fstream>
#include <sstream>

//---------------------Constructor y Destructor-----------------------------
Prestamo::Prestamo(string codigo_biblioteca, string ISBN, string usuario_id, string fecha_prestamo) {
    this->codigo_biblioteca = codigo_biblioteca;
    this->ISBN = ISBN;
    this->usuario_id = usuario_id; // Preguntar como es el tema
    this->fecha_prestamo = fecha_prestamo; // Formato: "YYYY-MM-DD"
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

//----------------------Metodos requeridos punto b -----------------------------

int Prestamo::totalPrestamosDeBiblioteca_Durante_(vector<Prestamo*> prestamos, string codigo, string fechaInicio, string fechaFin) {
    int totalPrestamos = 0;
    bool codigoEncontrado = false;
    for (Prestamo* prestamo : prestamos) {
        if (prestamo->getCodigoBiblioteca() == codigo) {
            codigoEncontrado = true;
            string fechaPrestamo = prestamo->getFechaPrestamo();
            if (fechaPrestamo >= fechaInicio && fechaPrestamo <= fechaFin) {
                totalPrestamos++;
            }
        }
    }
    if (!codigoEncontrado) {
        cout << "No existe la biblioteca con codigo: " << codigo << endl;
        return -1; // Indica que no se encontraron prestamos para el codigo dado
    }
    return totalPrestamos; // Retorna el total de prestamos encontrados en el rango de fechas
}

//necesito que la funcion de abajo no repita los prestamos en el vector de salida
vector<string> Prestamo::detectarBibliotecasConAltaCargaSemanal(vector<Prestamo*> prestamos, int cantidadDePrestamos, string fechaInicio, string fechaFin) {
    vector<string> bibliotecasConAltaCarga;
    set<string> bibliotecasAgregadas;
    for (Prestamo* prestamo : prestamos) {
        string codigoBiblioteca = prestamo->getCodigoBiblioteca();
        string fechaPrestamo = prestamo->getFechaPrestamo();
        if (fechaPrestamo >= fechaInicio && fechaPrestamo <= fechaFin) {
            if (bibliotecasAgregadas.find(codigoBiblioteca) == bibliotecasAgregadas.end()) {
                int totalPrestamos = totalPrestamosDeBiblioteca_Durante_(prestamos, codigoBiblioteca, fechaInicio, fechaFin);
                if (totalPrestamos > cantidadDePrestamos) {
                    bibliotecasConAltaCarga.push_back(codigoBiblioteca);
                    bibliotecasAgregadas.insert(codigoBiblioteca);
                }
            }
        }
    }
    return bibliotecasConAltaCarga;
}

vector<Prestamo> Prestamo::obtenerPrestamosDeUsuarioPorISBN(vector<Prestamo*> prestamos, string ISBN) {
    vector<Prestamo> prestamosUsuario;
    for (Prestamo* prestamo : prestamos) {
        if (prestamo->getISBN() == ISBN) {
            prestamosUsuario.push_back(*prestamo);
        }
    }
    return prestamosUsuario;
}


void Prestamo::cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos){
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    while (getline(archivo, linea)){
        istringstream ss(linea);
        vector<string> infoPrestamo;
        string palabra;
        while (ss >> palabra)
            infoPrestamo.push_back(palabra);
        if (infoPrestamo.size() >= 4){
            Prestamo *prestamoCreado = new Prestamo(
                infoPrestamo[0],
                infoPrestamo[1],
                infoPrestamo[2],
                infoPrestamo[3]);
            prestamos.push_back(prestamoCreado);
        }
    }
    archivo.close();
}