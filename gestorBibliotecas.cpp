#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "biblioteca.h"
#include "auxiliares.h"
// #include "tablaHash.h"
#include "arbol.h"

using namespace std;

void gestorBibliotecas()
{
    char operacion;
    bool aux = true;

    Arbol arbolBibliotecas;
    int cantidadBibliotecas = cargarBibliotecas("bibliotecas.txt", arbolBibliotecas);
    int tamanioTabla = cantidadBibliotecas / 0.8; // fijarnos esto
    // TablaHash tablaBiblioteca = TablaHash(tamanioTabla);
    //  falta recorrer arbol y cargar tabla

    arbolBibliotecas.inorden(arbolBibliotecas.getRaiz());

    do
    {

        cout << "Por favor, ingrese una opción: "
             << "A) Cargar biblioteca. " << std::endl
             << "B) Buscar biblioteca por codigo.  " << std::endl
             << "C) Eliminar biblioteca existente   " << std::endl
             << "D) Mostrar todas las bibliotecas  " << std::endl
             << "E) Calcular distancia entre bibliotecas   " << std::endl
             << "F) Calcular el total de prestamos de biblioteca   " << std::endl
             << "G) Detectar bibliotecas con alta carga  " << std::endl
             << "H) Buscar todos los prestamos de usuario por ISBN " << std::endl
             << "I) Salir del menu " << std::endl
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
            cout << "Por favor, ingrese el codigo de la biblioteca que desea cargar: ";
            cin >> codigo;
            cout << "Por favor, ingrese el nombre de la biblioteca que desea cargar: ";
            cin >> nombre;
            cout << "Por favor, ingrese la ciudad de la biblioteca que desea cargar: ";
            cin >> ciudad;
            cout << "Por favor, ingrese la superficie de la biblioteca que desea cargar: ";
            cin >> superficie;
            cout << "Por favor, ingrese la cantidad de libros de la biblioteca que desea cargar: ";
            cin >> cantidadLibros;
            cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea cargar: ";
            cin >> cantidadUsuarios;

            Biblioteca *bibliotecaACargar = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
            arbolBibliotecas.insertar(bibliotecaACargar);
            // agregar en tabla hash
            // preguntar si hay q cargarlo en el archivo
            break;
        }
        case 'b':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            string codigoBibliotecaABuscar;
            cout << "Por favor, ingrese el nombre del producto que desea buscar: ";
            cin >> codigoBibliotecaABuscar;
            arbolBibliotecas.buscar(arbolBibliotecas.getRaiz(), codigoBibliotecaABuscar);

            break;
        }
        case 'c':
        {
            // ERROR AL QUERER BORRAR RAIZ, ARREGLAR
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            // falta borrar en la tabla
            string codigoBibliotecaABorrar;
            cout << "Por favor, ingrese el nombre de la biblioteca que desea eliminar: ";
            cin >> codigoBibliotecaABorrar;
            arbolBibliotecas.borrar(codigoBibliotecaABorrar);
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
            std::cout << "Saliendo del menu" << std::endl;
            aux = false;
            arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());

            break;
        default:
            std::cout << "Operación no válida." << std::endl;
        }
    } while (aux);

    arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());
}