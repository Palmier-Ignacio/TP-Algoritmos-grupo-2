#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include "Biblioteca.h"
#include "Prestamo.h"
#include "arbol.h"

using namespace std;

int cargarBibliotecas(string nombreArchivo,Arbol& arbol)
{
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    int contadorBibliotecas=0;

    while (getline(archivo, linea))
    {
        contadorBibliotecas++;
        istringstream ss(linea);
        vector<string> infoBiblioteca;
        string palabra;

        // aca guardamos cada pslabra en un vector
        while (ss >> palabra)
        {
            infoBiblioteca.push_back(palabra);
        }

        // si estan todos los datos, se crea una biblioteca con las palabras de la linea
        if (infoBiblioteca.size() >= 6)
        {
            Biblioteca *bibliotecaCreada = new Biblioteca(
                infoBiblioteca[0],
                infoBiblioteca[1]+ " " +infoBiblioteca[2],
                infoBiblioteca[3],
                stoi(infoBiblioteca[4]),
                stoi(infoBiblioteca[5]),
                stoi(infoBiblioteca[6]));

            arbol.insertar(bibliotecaCreada);
        }
       
    }

    archivo.close();

    return contadorBibliotecas;
   
}


void cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos){
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    while (getline(archivo, linea)){
        istringstream ss(linea);
        vector<string> infoPrestamo;
        string palabra;
        while (ss >> palabra){
            infoPrestamo.push_back(palabra);
        }
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


int totalPrestamosDeBiblioteca_Durante_(vector<Prestamo*> prestamos, string codigo, string fechaInicio, string fechaFin) {
    // Esta funcion recibe un vector de prestamos, un codigo de biblioteca y un rango de fechas
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
vector<string> detectarBibliotecasConAltaCargaSemanal(vector<Prestamo*> prestamos, int cantidadDePrestamos, string fechaInicio, string fechaFin) {
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

vector<Prestamo> obtenerPrestamosDeUsuarioPorISBN(vector<Prestamo*> prestamos, string ISBN) {
    vector<Prestamo> prestamosUsuario;
    for (Prestamo* prestamo : prestamos) {
        if (prestamo->getISBN() == ISBN) {
            prestamosUsuario.push_back(*prestamo);
        }
    }
    return prestamosUsuario;
}