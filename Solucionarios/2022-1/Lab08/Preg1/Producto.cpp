/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Producto.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Producto.h"
using namespace std;

Producto::Producto() {
    codprod = 0;
    nombre = nullptr;
}

Producto::Producto(const Producto& orig) {
    cerr << "Constructor copia de Producto" << endl;
}

Producto::~Producto() {
    if (nombre) delete nombre;
}

/* Métodos */

void Producto::leerProducto(ifstream& arch) {
    char nombre[50], c;
    arch >> codprod >> c;
    if (arch.eof()) return;
    arch.getline(nombre, 50, ',');
    setNombre(nombre);
    arch >> precio >> c >> stock;
}

/* Encapsulamiento */

int Producto::getCodProd() const {
    return codprod;
}
void Producto::setCodProd(int codprod) {
    this->codprod = codprod;
}

void Producto::getNombre(char* nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}
void Producto::setNombre(const char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}

double Producto::getPrecio() const {
    return precio;
}
void Producto::setPrecio(double precio) {
    this->precio = precio;
}

int Producto::getStock() const {
    return stock;
}
void Producto::setStock(int stock) {
    this->stock = stock;
}
