/*
 * File:   Libro.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 12 de noviembre de 2021, 09:18 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "LibroPrestado.h"
#include "Libro.h"
using namespace std;

Libro::Libro() {
    codigo = nullptr;
    titulo = nullptr;
    autor = nullptr;
    cantDoc = 0;
    cantEst = 0;
    cantAdm = 0;
    prestados = 0;
    stock = 0;
}

Libro::Libro(const Libro& orig) {
}

Libro::~Libro() {
    if (codigo) delete codigo;
    if (titulo) delete titulo;
    if (autor) delete autor;
}

/* Métodos */

ifstream& Libro::leer(ifstream& arch) {
    char codigo[10], titulo[50], autor[50], c;
    int anio, stock;
    double precio;
    // Leer los datos del archivo
    arch.getline(codigo, 10, ',');
    if (arch.eof()) return arch;
    arch.getline(titulo, 50, ',');
    arch.getline(autor, 50, ',');
    arch >> anio >> c >> stock >> c >> precio >> ws;
    // Colocar los datos en el objeto
    SetCodigo(codigo);
    SetTitulo(titulo);
    SetAutor(autor);
    SetStock(stock);
    SetPrecio(precio);
    return arch;
}

ofstream& Libro::imprimir(ofstream& arch) {
    char codigo[10], titulo[50], autor[50];
    GetCodigo(codigo);
    GetTitulo(titulo);
    GetAutor(autor);
    arch << setprecision(2);
    arch << "Codigo: " << codigo << endl;
    arch << "Titulo: " << titulo << endl;
    arch << "Autor:  " << autor << endl;
    arch << "Stock:  " << GetStock() << endl;
    imprimirLinea(arch, '=');
    arch << "Prestamo a docentes: " << setw(9) << GetCantDoc() << endl; 
    arch << "Prestamo a alumnos: " << setw(10) << GetCantEst() << endl; 
    arch << "Prestamo a administradores: " << setw(2) << GetCantAdm() << endl; 
    imprimirLinea(arch, '-');
    arch << "Total de prestamos: " << setw(10) << GetPrestados() << endl;
    imprimirLinea(arch, '=');
    return arch;
}

void Libro::imprimirLinea(ofstream& arch, char c) {
    for (int i = 0; i < 40; i++) {
        arch.put(c);
    }
    arch << endl;
}

/* Sobrecargas */

void Libro::operator +=(LibroPrestado& libPrest) {
    prestados++;
    switch (libPrest.getTipo()) {
        case 'D':
            cantDoc++;
            break;
        case 'E':
            cantEst++;
            break;
        case 'A':
            cantAdm++;
            break;
    }
}

ifstream& operator >>(ifstream& arch, Libro& libro) {
    return libro.leer(arch);
}

ofstream& operator <<(ofstream& arch, Libro& libro) {
    return libro.imprimir(arch);
}

/* Encapsulamiento */

void Libro::GetAutor(char* autor) const {
    if (this->autor) strcpy(autor, this->autor);
    else autor[0] = 0;
}

void Libro::SetAutor(char* autor) {
    if (this->autor) delete this->autor;
    this->autor = new char[strlen(autor)+1];
    strcpy(this->autor, autor);
}

int Libro::GetCantAdm() const {
    return cantAdm;
}

void Libro::SetCantAdm(int cantAdm) {
    this->cantAdm = cantAdm;
}

int Libro::GetCantDoc() const {
    return cantDoc;
}

void Libro::SetCantDoc(int cantDoc) {
    this->cantDoc = cantDoc;
}

int Libro::GetCantEst() const {
    return cantEst;
}

void Libro::SetCantEst(int cantEst) {
    this->cantEst = cantEst;
}

void Libro::GetCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void Libro::SetCodigo(char* codigo) {
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

int Libro::GetPrestados() const {
    return prestados;
}

void Libro::SetPrestados(int prestados) {
    this->prestados = prestados;
}

int Libro::GetStock() const {
    return stock;
}

void Libro::SetStock(int stock) {
    this->stock = stock;
}

void Libro::GetTitulo(char *titulo) const {
    if (this->titulo) strcpy(titulo, this->titulo);
    else titulo[0] = 0;
}

void Libro::SetTitulo(char* titulo) {
    if (this->titulo) delete this->titulo;
    this->titulo = new char[strlen(titulo)+1];
    strcpy(this->titulo, titulo);
}
