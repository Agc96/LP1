/*
 * File:   Libro.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 3 de diciembre de 2021, 08:13 AM
 */

#include <cstring>
#include "Libro.h"
using namespace std;

Libro::Libro() {
    codigo = nullptr;
    titulo = nullptr;
    autor = nullptr;
}

Libro::Libro(const Libro& orig) {
}

Libro::~Libro() {
    if (codigo) delete codigo;
    if (titulo) delete titulo;
    if (autor) delete autor;
}

/* Encapsulamiento */

int Libro::GetAnho() const {
    return anho;
}

void Libro::SetAnho(int anho) {
    this->anho = anho;
}

void Libro::GetAutor(char* autor) const {
    if (this->autor) strcpy(autor, this->autor);
    else autor[0] = 0;
}

void Libro::SetAutor(const char* autor) {
    if (this->autor) delete this->autor;
    this->autor = new char[strlen(autor)+1];
    strcpy(this->autor, autor);
}

int Libro::GetCantidad() const {
    return cantidad;
}

void Libro::SetCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void Libro::GetCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void Libro::SetCodigo(const char* codigo) {
    if (this->codigo) delete this->codigo;
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

double Libro::GetPrecio() const {
    return precio;
}

void Libro::SetPrecio(double precio) {
    this->precio = precio;
}

int Libro::GetStock() const {
    return stock;
}

void Libro::SetStock(int stock) {
    this->stock = stock;
}

void Libro::GetTitulo(char* titulo) const {
    if (this->titulo) strcpy(titulo, this->titulo);
    else titulo[0] = 0;
}

void Libro::SetTitulo(const char* titulo) {
    if (this->titulo) delete this->titulo;
    this->titulo = new char[strlen(titulo)+1];
    strcpy(this->titulo, titulo);
}
