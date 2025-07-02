#include "prestamo.h"
#include <ctime>
#include <fstream>
#include <sstream>

//---------------------Constructor y Destructor-----------------------------
Prestamo::Prestamo(string codigo_biblioteca, string ISBN, string usuario_id, string fecha_prestamo) {
    this->codigo_biblioteca = codigo_biblioteca;
    this->ISBN = ISBN;
    this->usuario_id = usuario_id; // Preguntar como es el tema
    this->fecha_prestamo = fecha_prestamo; // Formato: "YYYYMMDD"
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


vector<string> Prestamo::detectarBibliotecasConAltaCargaSemanal(vector<Prestamo*> prestamos, int cantidadDePrestamos) {

    set<string> bibliotecasConAltaCarga; 
    for (Prestamo* prestamo : prestamos) {
        string codigoBiblioteca = prestamo->getCodigoBiblioteca();
        string fechaPrestamo = prestamo->getFechaPrestamo();
        
  
        int anio = stoi(fechaPrestamo.substr(0, 4));
        int mes = stoi(fechaPrestamo.substr(4, 2)); 
        int dia = stoi(fechaPrestamo.substr(6, 2));
        
        tm fechaAntes = {0};
        fechaAntes.tm_year = anio - 1900; // restamos 1900 porque tm_year es el año desde 1900
        fechaAntes.tm_mon = mes - 1; // restamos 1 porque tm_mon es de 0 a 11
        fechaAntes.tm_mday = dia - 6; // Restamos 6 días
        mktime(&fechaAntes); // si el dia es negativo va para el mes anterior, si es mayor, al siguiente mes
        string fechaUnaSemanaAntes = to_string(fechaAntes.tm_year + 1900) +
                                     (fechaAntes.tm_mon + 1 < 10 ? "0" : "") + to_string(fechaAntes.tm_mon + 1) +
                                     (fechaAntes.tm_mday < 10 ? "0" : "") + to_string(fechaAntes.tm_mday);
        
        tm fechaDespues = {0};
        fechaDespues.tm_year = anio - 1900; 
        fechaDespues.tm_mon = mes - 1; 
        fechaDespues.tm_mday = dia + 6; 
        mktime(&fechaDespues); 
        string fechaUnaSemanaDespues = to_string(fechaDespues.tm_year + 1900) +
                                       (fechaDespues.tm_mon + 1 < 10 ? "0" : "") + to_string(fechaDespues.tm_mon + 1) +
                                       (fechaDespues.tm_mday < 10 ? "0" : "") + to_string(fechaDespues.tm_mday);


        int contadorAntes = 0;
        int contadorDespues = 0;
        for (Prestamo* otroPrestamo : prestamos) {
            string otraFechaPrestamo = otroPrestamo->getFechaPrestamo();
            if (otroPrestamo->getCodigoBiblioteca() == codigoBiblioteca) {
                if (otraFechaPrestamo >= fechaUnaSemanaAntes && otraFechaPrestamo < fechaPrestamo) {
                    contadorAntes++;
                }
                if (otraFechaPrestamo > fechaPrestamo && otraFechaPrestamo <= fechaUnaSemanaDespues) {
                    contadorDespues++;
                }
            }
        }
        // Si alguno de los contadores supera la cantidad de prestamos, agregamos el codigo al set
        if (contadorAntes >= cantidadDePrestamos || contadorDespues >= cantidadDePrestamos
            || contadorAntes + contadorDespues >= cantidadDePrestamos) {
            bibliotecasConAltaCarga.insert(codigoBiblioteca);
        }



    
}
    // Convertimos el set a un vector para devolverlo
    vector<string> resultado(bibliotecasConAltaCarga.begin(), bibliotecasConAltaCarga.end());

    return resultado; 
}


vector<Prestamo> Prestamo::obtenerPrestamosDeUsuarioPorISBN(vector<Prestamo*> prestamos, string codigoUsuario) {
 
    vector<Prestamo> prestamosUsuario;
    for (Prestamo* prestamo : prestamos) {
        if (prestamo->getUsuarioId() == codigoUsuario) {
            prestamosUsuario.push_back(*prestamo);
        }
    }
    if (prestamosUsuario.empty()) {
        cout << "No se encontraron prestamos para el usuario con ID: " << codigoUsuario << endl;
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