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

using namespace std;

void gestorBibliotecas()
{
    char operacion;
    bool aux = true;

    Arbol arbolBibliotecas;
    int cantidadBibliotecas = Biblioteca::cargarBibliotecas("bibliotecas.txt", arbolBibliotecas);
    int tamanioTabla = cantidadBibliotecas / 0.8; // fijarnos esto
    TablaHash tablaBiblioteca = TablaHash(tamanioTabla);
    arbolBibliotecas.recorreEInsertaEnTabla(arbolBibliotecas.getRaiz(), tablaBiblioteca);

    Grafo *grafo = Grafo::crearDesdeArchivo("bibliotecasDistancias.txt");
    if (!grafo)
    {
        cout << "Error cargando el grafo de distancias." << endl;
        return;
    }

    grafo->floydWarshall(); // Ejecutar algoritmo una sola vez al inicio

    vector<Prestamo *> prestamos;
    Prestamo::cargarPrestamos("prestamos.txt", prestamos);

    do
    {
        cout << std::endl
             << "Por favor, ingrese una opción: " << std::endl
             << "A) Cargar biblioteca. " << std::endl
             << "B) Buscar biblioteca.  " << std::endl
             << "C) Eliminar biblioteca existente   " << std::endl
             << "D) Mostrar todas las bibliotecas  " << std::endl
             << "E) Calcular distancia entre bibliotecas   " << std::endl
             << "F) Calcular el total de prestamos de biblioteca durante un periodo  " << std::endl
             << "G) Detectar bibliotecas con alta carga en una semana " << std::endl
             << "H) Buscar todos los prestamos de usuario por ISBN " << std::endl
             << "I) Mostrar bibliotecas en TablaHash " << std::endl
             << "J) Salir del menu " << std::endl
             << std::endl;
        std::cin >> operacion;
        operacion = std::tolower(operacion);

        switch (operacion)
        {
        case 'a':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigo;
            string nombre;
            string ciudad;
            float superficie;
            int cantidadLibros;
            int cantidadUsuarios;
            cout << "Por favor, ingrese el codigo de la biblioteca que desea cargar: " << std::endl;
            cin >> codigo;
            cout << "Por favor, ingrese el nombre de la biblioteca que desea cargar: " << std::endl;
            cin >> nombre;
            cout << "Por favor, ingrese la ciudad de la biblioteca que desea cargar: " << std::endl;
            cin >> ciudad;
            cout << "Por favor, ingrese la superficie de la biblioteca que desea cargar: " << std::endl;
            cin >> superficie;
            cout << "Por favor, ingrese la cantidad de libros de la biblioteca que desea cargar: " << std::endl;
            cin >> cantidadLibros;
            cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea cargar: " << std::endl;
            cin >> cantidadUsuarios;

            Biblioteca *bibliotecaACargar = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
            if (arbolBibliotecas.insertar(bibliotecaACargar))
            {
                cout << "Se añadio con exito al arbol la biblioteca con codigo: " << bibliotecaACargar->getCodigo() << endl;
            }
            else
            {
                cout << "No se pudo añadir la biblioteca en el arbol." << endl;
            }

            tablaBiblioteca.insertar(codigo);
            break;
        }
        case 'b':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBibliotecaABuscar;
            int cantUsuariosBiblioteca;
            cout << "Por favor, ingrese el codigo de la biblioteca que desea buscar: ";
            cin >> codigoBibliotecaABuscar;
            cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea buscar: ";
            cin >> cantUsuariosBiblioteca;
            arbolBibliotecas.buscar(arbolBibliotecas.getRaiz(), codigoBibliotecaABuscar, cantUsuariosBiblioteca);
            tablaBiblioteca.buscarBiblioteca(codigoBibliotecaABuscar);
            break;
        }
        case 'c':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBibliotecaABorrar;
            int cantUsuariosBiblioteca;
            cout << "Por favor, ingrese el codigo de la biblioteca que desea eliminar: ";
            cin >> codigoBibliotecaABorrar;
            cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea eliminar: ";
            cin >> cantUsuariosBiblioteca;
            bool seBorroEnArbol= arbolBibliotecas.borrar(codigoBibliotecaABorrar, cantUsuariosBiblioteca);
            if (seBorroEnArbol)
                tablaBiblioteca.eliminar(codigoBibliotecaABorrar);
        }
        break;
        case 'd':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            arbolBibliotecas.inorden(arbolBibliotecas.getRaiz());
            break;
        case 'e':
        {
            cout << "Ingrese biblioteca origen: ";
            string origen;
            cin >> origen;
            cout << "Ingrese biblioteca destino: ";
            string destino;
            cin >> destino;

            int idxOrigen = grafo->obtenerIndicePorNombre(origen);
            int idxDestino = grafo->obtenerIndicePorNombre(destino);

            if (idxOrigen == -1 || idxDestino == -1)
            {
                cout << "Alguna biblioteca no fue encontrada." << endl;
                break;
            }

            // Obtener distancia mínima
            double distancia = grafo->obtenerDistancia(idxOrigen, idxDestino);

            if (distancia == std::numeric_limits<double>::infinity())
            {
                cout << "No hay camino entre las bibliotecas." << endl;
                break;
            }
            cout << "Distancia mínima: " << distancia << endl;

            // Obtener camino mínimo
            vector<string> camino = grafo->obtenerCaminoMinimo(idxOrigen, idxDestino);
            cout << "Camino mínimo: ";
            for (const auto &biblio : camino)
            {
                cout << biblio;
                if (&biblio != &camino.back())
                    cout << " -> ";
            }
            cout << endl;
            break;
        }

        case 'f':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBiblioteca;
            string fechaInicio;
            string fechaFin;

            cout << "Por favor, ingrese el codigo de la biblioteca: ";
            cin >> codigoBiblioteca;

            cout << "Por favor, ingrese la fecha de inicio (YYYYMMDD): ";
            cin >> fechaInicio;

            cout << "Por favor, ingrese la fecha de fin (YYYYMMDD): ";
            cin >> fechaFin;

            // Si la biblioteca fue encontrada, llamamos al método totalPrestamosDeBiblioteca_Durante_
            int totalPrestamos = Prestamo::totalPrestamosDeBiblioteca_Durante_(prestamos, codigoBiblioteca, fechaInicio, fechaFin);
            if (totalPrestamos >= 0)
            {
                cout << "Total de prestamos de la biblioteca " << codigoBiblioteca << " durante el periodo "
                     << fechaInicio << " a " << fechaFin << ": " << totalPrestamos << endl;
            }
            else
                cout << "No se encontraron prestamos para la biblioteca con codigo: " << codigoBiblioteca << endl;
            break;
        }
        case 'g':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            int cantidadDePrestamos;
            string fechaInicioAltaCarga;
            string fechaFinAltaCarga;
            cout << "Por favor, ingrese la cantidad de prestamos que desea considerar para alta carga: ";
            cin >> cantidadDePrestamos;
            cout << "Por favor, ingrese la fecha de inicio (YYYYMMDD): ";
            cin >> fechaInicioAltaCarga;
            cout << "Por favor, ingrese la fecha de fin (YYYYMMDD): ";
            cin >> fechaFinAltaCarga;
            vector<string> bibliotecasConAltaCarga = Prestamo::detectarBibliotecasConAltaCargaSemanal(prestamos, cantidadDePrestamos, fechaInicioAltaCarga, fechaFinAltaCarga);
            if (bibliotecasConAltaCarga.empty())
                cout << "No se encontraron bibliotecas con alta carga en el periodo especificado." << endl;
            else
            {
                cout << "Bibliotecas con alta carga en el periodo " << fechaInicioAltaCarga << " a " << fechaFinAltaCarga << ":" << endl;
                for (const string &codigo : bibliotecasConAltaCarga)
                    cout << "- " << codigo << endl;
            }
            break;
        }
        case 'h':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string ISBN;
            cout << "Por favor, ingrese el ISBN del libro: ";
            cin >> ISBN;
            vector<Prestamo> prestamosUsuario = Prestamo::obtenerPrestamosDeUsuarioPorISBN(prestamos, ISBN);
            if (prestamosUsuario.empty())
                cout << "No se encontraron prestamos para el ISBN: " << ISBN << endl;
            else
            {
                cout << "Prestamos encontrados para el ISBN " << ISBN << ":" << endl;
                for (Prestamo &prestamo : prestamosUsuario)
                    prestamo.mostrar();
            }
            break;
        }
        case 'i':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            tablaBiblioteca.mostrarBibliotecas();
            break;
        case 'j':
            cout << "Saliendo del menu" << endl;
            aux = false;
            arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());
            delete grafo; // liberar memoria del grafo

            for (Prestamo *prest : prestamos)
                delete prest;
            // prestamos.clear();
            break;
        default:
            std::cout << "Operación no válida." << std::endl;
        }
        Sleep(3000);
    } while (aux);
}