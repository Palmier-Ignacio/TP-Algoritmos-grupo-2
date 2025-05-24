#include "biblioteca.h"
Biblioteca::Biblioteca(string codigo, string nombre, string ciudad, float superficie, int cantidadLibros, int cantidadUsuarios)
{
    this->codigo = codigo;
    this->nombre = nombre;
    this->ciudad = ciudad;
    this->superficie = superficie;
    this->cantidadLibros = cantidadLibros;
    this->cantidadUsuarios = cantidadUsuarios;
}

Biblioteca::~Biblioteca()
{
    /* fijarse si hay q liberar mem */
}

void Biblioteca::mostrar()
{
    cout << "Biblioteca: " << this->codigo << " " <<  this->nombre << " " << this->ciudad << " " <<  this->superficie << " " <<  this->cantidadLibros << " " << this->cantidadUsuarios << endl;
}

string Biblioteca::getCodigo()
{
    return codigo;
}
string Biblioteca::getNombre()
{
    return nombre;
}

string Biblioteca::getCiudad()
{
    return ciudad;
}

float Biblioteca::getSuperficie()
{
    return superficie;
}

int Biblioteca::getCantidadLibros()
{
    return cantidadLibros;
}

int Biblioteca::getCantidadUsuarios()
{
    return cantidadUsuarios;
}
void Biblioteca::setCodigo(string nuevoCodigo)
{
    codigo = nuevoCodigo;
}

void Biblioteca::setNombre(string nuevoNombre)
{
    nombre = nuevoNombre;
}
void Biblioteca::setCiudad(string nuevaCiudad)
{
    ciudad = nuevaCiudad;
}
void Biblioteca::setSuperficie(float nuevaSuperficie)
{
    superficie = nuevaSuperficie;
}
void Biblioteca::setCantidadLibros(int nuevaCantidadLibros)
{
    cantidadLibros = nuevaCantidadLibros;
}
void Biblioteca::setCantidadUsuarios(int nuevaCantidadUsuarios)
{
    cantidadUsuarios = nuevaCantidadUsuarios;
}