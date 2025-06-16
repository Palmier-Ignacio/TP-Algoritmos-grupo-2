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

using namespace std;

void gestorBibliotecas()
{
    char operacion;
    bool aux = true;

    Arbol arbolBibliotecas;
    int cantidadBibliotecas = cargarBibliotecas("bibliotecas.txt", arbolBibliotecas);
    int tamanioTabla = cantidadBibliotecas / 0.8; // fijarnos esto
    TablaHash tablaBiblioteca = TablaHash(tamanioTabla);

    arbolBibliotecas.inorden(arbolBibliotecas.getRaiz());
    arbolBibliotecas.recorreEInsertaEnTabla(arbolBibliotecas.getRaiz(),tablaBiblioteca); 

    do
    {


        cout << std::endl << "Por favor, ingrese una opción: "<< std::endl
             << "A) Cargar biblioteca. " << std::endl
             << "B) Buscar biblioteca por codigo.  " << std::endl
             << "C) Eliminar biblioteca existente   " << std::endl
             << "D) Mostrar todas las bibliotecas  " << std::endl
             << "E) Calcular distancia entre bibliotecas   " << std::endl
             << "F) Calcular el total de prestamos de biblioteca   " << std::endl
             << "G) Detectar bibliotecas con alta carga  " << std::endl
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
            arbolBibliotecas.insertar(bibliotecaACargar);
            tablaBiblioteca.insertar(codigo);
            // agregar en tabla hash
            // preguntar si hay q cargarlo en el archivo
            break;
        }
        case 'b':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBibliotecaABuscar;
            cout << "Por favor, ingrese el codigo de la biblioteca que desea buscar: ";
            cin >> codigoBibliotecaABuscar;
            arbolBibliotecas.buscar(arbolBibliotecas.getRaiz(), codigoBibliotecaABuscar);
            tablaBiblioteca.buscarBiblioteca(codigoBibliotecaABuscar);

            break;
        }
        case 'c':
        {
            // ERROR AL QUERER BORRAR RAIZ, ARREGLAR
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBibliotecaABorrar;
            cout  << "Por favor, ingrese el nombre de la biblioteca que desea eliminar: ";
            cin >> codigoBibliotecaABorrar;
            arbolBibliotecas.borrar(codigoBibliotecaABorrar);
            tablaBiblioteca.eliminar(codigoBibliotecaABorrar);
        }

        break;
        case 'd':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            //PREGUNTAR SI HAY QUE DAR LAS TRES OPCIONES O SI ELEGIMOS NOSOTROS
            // DE MOMENTO PONGO EN INORDEN ORDENADAS POR CODIGO
            arbolBibliotecas.inorden(arbolBibliotecas.getRaiz());
            break;
        case 'e':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'f':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'g':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'h':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;

            break;
        case 'i':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            tablaBiblioteca.mostrarBibliotecas(); 
            break; 
        case 'j':
            std::cout << "Saliendo del menu" << std::endl;
            aux = false;
            arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());

            break;
        default:
            std::cout << "Operación no válida." << std::endl;
        }
    Sleep(3000); 
    } while (aux);
    arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());
}