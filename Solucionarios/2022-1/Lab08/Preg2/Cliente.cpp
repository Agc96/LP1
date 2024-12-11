/*
 * Archivo: Cliente.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Cliente.h"
using namespace std;

Cliente::Cliente() {
    dni = 0;
    nombre = nullptr;
}

Cliente::Cliente(const Cliente& orig) {
    cerr << "Constructor copia de Cliente" << endl;
}

Cliente::~Cliente() {
    if (nombre) delete nombre;
}

/* Métodos */

void Cliente::leer(ifstream& arch) {
    char nombre[50];
    arch >> dni;
    if (arch.eof()) return;
    arch.get();
    arch.getline(nombre, 50, ',');
    SetNombre(nombre);
    categoria = arch.get();
}

void Cliente::imprimir(ofstream& arch) {
    char nombre[50];
    GetNombre(nombre);
    arch << left << setw(10) << dni << setw(50) << nombre << categoria << endl;
}

/* Encapsulamiento */

char Cliente::GetCategoria() const {
    return categoria;
}
void Cliente::SetCategoria(char categoria) {
    this->categoria = categoria;
}

int Cliente::GetDni() const {
    return dni;
}
void Cliente::SetDni(int dni) {
    this->dni = dni;
}

void Cliente::GetNombre(char *nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}
void Cliente::SetNombre(const char* nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}
