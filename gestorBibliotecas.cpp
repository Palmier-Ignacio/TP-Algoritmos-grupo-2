#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "biblioteca.h"
#include "auxiliares.h"
#include "tablaHash.h"


using namespace std;

void gestorBibliotecas()
{
    char operacion;
    bool aux = true;

    vector<Biblioteca*> biblioteca = {};
    int cantidadBibliotecas = cargarBibliotecas("bibliotecas.txt", biblioteca);
    int tamanioTabla = cantidadBibliotecas/0.8;//fijarnos esto
    TablaHash tablaBiblioteca =TablaHash(tamanioTabla);
    // recorrer arbol y cargar tabla

    do
    {

        cout << "Por favor, ingrese una opción: "
             << "A) Cargar biblioteca. " << std::endl
             << "B) Buscar biblioteca por codigo.  " << std::endl
             << "C) Eliminar biblioteca existente   " << std::endl
             << "D) Mostrar todas las bibliotecas (poner las opciones)   " << std::endl
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

            break;
        }
        case 'b':
        {
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            
            break;
        }
        case 'c':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'd':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'e':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'f':
            std::cout << "La opción que usted eligió es " << operacion << std::endl;
            break;
        case 'g':
            std::cout << "Cargar productos al chango" << operacion << std::endl;
            break;
        case 'h':
            std::cout << "Saliendo del menu" << std::endl;
            
            break;
         case 'i':
            std::cout << "Saliendo del menu" << std::endl;
            aux = false;
            break;
        default:
            std::cout << "Operación no válida." << std::endl;
        }
    } while (aux);
}