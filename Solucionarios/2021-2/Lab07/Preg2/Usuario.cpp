/*
 * File:   Usuario.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 12 de noviembre de 2021, 09:16 AM
 */

#include <cstring>
#include "Usuario.h"
using namespace std;

Usuario::Usuario() {
    nombre = nullptr;
    numLibPrest = 0;
    carne = 0;
    condicion = 1;
}

Usuario::Usuario(const Usuario& orig) {
}

Usuario::~Usuario() {
    if (nombre) delete nombre;
}

/* Métodos */

ifstream& Usuario::leer(ifstream& arch) {
    char nombre[50], tipo, c;
    int carne;
    // Leer los datos del archivo
    arch >> carne;
    if (arch.eof()) return arch;
    arch >> tipo >> c >> nombre;
    // Colocar los datos en el objeto
    SetCarne(carne);
    SetTipo(tipo);
    SetNombre(nombre);
    return arch;
}

ofstream& Usuario::imprimir(ofstream& arch) {
    char nombre[50];
    // Imprimir la cabecera del reporte
    arch << "Carne: " << GetCarne() << endl;
    GetNombre(nombre);
    arch << nombre << endl;
    imprimirTipo(arch);
    imprimirCondicion(arch);
    // Imprimir la relación de libros prestados
    for (int i = 0; i < numLibPrest; i++) {
        arch << libPrest[i];
    }
    return arch;
}

void Usuario::imprimirTipo(ofstream& arch) {
    switch (GetTipo()) {
        case 'E':
            arch << "Estudiante" << endl;
            break;
        case 'D':
            arch << "Docente" << endl;
            break;
        case 'A':
            arch << "Administrador" << endl;
            break;
    }
}

void Usuario::imprimirCondicion(ofstream& arch) {
    if (GetCondicion()) arch << "HABILITADO" << endl;
    else arch << "INHABILITADO" << endl;
}

/* Sobrecargas */

void Usuario::operator +=(LibroPrestado& prestamo) {
    libPrest[numLibPrest] = prestamo;
    numLibPrest++;
}

void Usuario::operator *(int fecha) {
    SetCondicion(1);
    for (int i = 0; i < numLibPrest; i++) {
        libPrest[i].calcularDeuda(fecha);
        if (libPrest[i].getDeuda()) SetCondicion(0);
    }
}

ifstream& operator >>(ifstream& arch, Usuario& usuario) {
    return usuario.leer(arch);
}

ofstream& operator <<(ofstream& arch, Usuario& usuario) {
    return usuario.imprimir(arch);
}

/* Encapsulamiento */

int Usuario::GetCarne() const {
    return carne;
}

void Usuario::SetCarne(int carne) {
    this->carne = carne;
}

void Usuario::GetNombre(char *nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}

void Usuario::SetNombre(char *nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}

char Usuario::GetTipo() const {
    return tipo;
}

void Usuario::SetTipo(char tipo) {
    this->tipo = tipo;
}

int Usuario::GetCondicion() const {
    return condicion;
}

void Usuario::SetCondicion(int condicion) {
    this->condicion = condicion;
}
