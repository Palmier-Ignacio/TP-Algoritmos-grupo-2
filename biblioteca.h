#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#include <iostream>
using namespace std;

class Biblioteca
{
private:
    // atributos
    string codigo;
    string nombre;
    string ciudad;
    float superficie;
    int cantidadLibros;
    int cantidadUsuarios;

public:
    // constructor
    // pos: crea una biblioteca con sus atributos
    Biblioteca(string codigo,string nombre,string ciudad,float superficie,int cantidadLibros,int cantidadUsuarios);

    // pos: libera la memoria
    virtual ~Biblioteca();
    
    // pos: imprime los datos de la biblioteca
    void mostrar();
    
    
    // pos: imprime el codigo de la biblioteca
    string getCodigo();
    // pos: imprime el nombre de la biblioteca
    string getNombre();
    // pos: imprime la ciudad de la biblioteca
    string getCiudad();
    // pos: imprime la superficie de la biblioteca
    float getSuperficie();
    // pos: imprime la cantidad de libros que tiene la biblioteca
    int getCantidadLibros();
    // pos: imprime la cantidad de usuarios que tiene la biblioteca
    int getCantidadUsuarios();
    
    // pos: setea el codigo de la biblioteca pasado por parametro
    void setCodigo(string nuevoCodigo);
    // pos: setea el nombre de la biblioteca pasado por parametro
    void setNombre(string nuevoNombre);
    // pos: setea el nombre de la ciudad de la biblioteca pasado por parametro
    void setCiudad(string nuevaCiudad);
    // pos: setea la superficie de la biblioteca pasado por parametro
    void setSuperficie(float nuevaSuperficie);
    // pos: setea la cantidad de libros de la biblioteca pasado por parametro
    void setCantidadLibros(int nuevaCantidadLibros);
    // pos: setea la cantidad de usuarios de la biblioteca pasado por parametro
    void setCantidadUsuarios(int nuevaCantidadUsuarios);

};

#endif 