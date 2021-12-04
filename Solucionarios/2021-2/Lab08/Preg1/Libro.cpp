/*
 * File:   Libro.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 21 de noviembre de 2021, 05:40 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Libro.h"
using namespace std;

#define MAX_LINEA 80

Libro::Libro() {
    codigo = nullptr;
    titulo = nullptr;
    autor = nullptr;
    cantidad = 0;
}

Libro::Libro(const Libro& orig) {
    codigo = nullptr;
    titulo = nullptr;
    autor = nullptr;
    copiar(orig);
}

Libro::~Libro() {
    if (codigo) delete codigo;
    if (titulo) delete titulo;
    if (autor) delete autor;
}

/* Métodos */

void Libro::leer(ifstream& arch) {
    char codigo[10], titulo[50], autor[50], c;
    int anio, cantidad;
    double precio;
    // Leer los datos del archivo
    arch.getline(codigo, 10, ',');
    arch.getline(titulo, 50, ',');
    arch.getline(autor, 50, ',');
    arch >> anio >> c >> cantidad >> c >> precio;
    // Colocar los datos en el objeto
    setCodigo(codigo);
    setTitulo(titulo);
    setAutor(autor);
    setCantidad(cantidad);
    setPrecio(precio);
}

void Libro::copiar(const Libro& orig) {
    char buffer[50];
    orig.getCodigo(buffer);
    setCodigo(buffer);
    orig.getTitulo(buffer);
    setTitulo(buffer);
    orig.getAutor(buffer);
    setAutor(buffer);
    setCantidad(orig.getCantidad());
    setPrecio(orig.getPrecio());
}

void Libro::imprimir(ofstream& arch, bool lineaInicial) {
    char codigo[10], titulo[50], autor[50];
    getCodigo(codigo);
    getTitulo(titulo);
    getAutor(autor);
    if (lineaInicial) {
        imprimirLinea(arch, '-');
    }
    arch << "Codigo: " << codigo << endl;
    arch << "Titulo: " << titulo << endl;
    arch << "Autor: " << autor << endl;
    arch << "Cantidad: " << getCantidad() << endl;
    imprimirLinea(arch, '-');
}

void Libro::imprimirLinea(ofstream& arch, char c) {
    for (int i = 0; i < MAX_LINEA; i++) {
        arch.put(c);
    }
    arch << endl;
}

/* Encapsulamiento */

void Libro::getAutor(char* autor) const {
    if (this->autor) strcpy(autor, this->autor);
    else autor[0] = 0;
}

void Libro::setAutor(char* autor) {
    if (this->autor) delete this->autor;
    this->autor = new char[strlen(autor)+1];
    strcpy(this->autor, autor);
}

int Libro::getCantidad() const {
    return cantidad;
}

void Libro::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void Libro::getCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void Libro::setCodigo(char* codigo) {
    if (this->codigo) delete this->codigo;
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

double Libro::getPrecio() const {
    return precio;
}

void Libro::setPrecio(double precio) {
    this->precio = precio;
}

void Libro::getTitulo(char* titulo) const {
    if (this->titulo) strcpy(titulo, this->titulo);
    else titulo[0] = 0;
}

void Libro::setTitulo(char* titulo) {
    if (this->titulo) delete this->titulo;
    this->titulo = new char[strlen(titulo)+1];
    strcpy(this->titulo, titulo);
}
