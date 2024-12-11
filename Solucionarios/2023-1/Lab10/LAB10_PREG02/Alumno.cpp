/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:17 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Alumno.h"
using namespace std;

Alumno::Alumno() {
    nombre = nullptr;
    total = 0;
}

Alumno::Alumno(const Alumno& orig) {
}

Alumno::~Alumno() {
    if (nombre) delete[] nombre;
}

/* Encapsulamiento */

int Alumno::GetCodigo() const {
    return codigo;
}

void Alumno::SetCodigo(int codigo) {
    this->codigo = codigo;
}

double Alumno::GetCreditos() const {
    return creditos;
}

void Alumno::SetCreditos(double creditos) {
    this->creditos = creditos;
}

int Alumno::GetEscala() const {
    return escala;
}

void Alumno::SetEscala(int escala) {
    this->escala = escala;
}

void Alumno::GetNombre(char *cad) const {
    if (nombre) strcpy(cad, nombre);
    else cad[0] = 0;
}

void Alumno::SetNombre(const char *cad) {
    if (nombre) delete[] nombre;
    nombre = new char[strlen(cad)+1];
    strcpy(nombre, cad);
}

double Alumno::GetTotal() const {
    return total;
}

void Alumno::SetTotal(double total) {
    this->total = total;
}

/* Métodos */

void Alumno::lee(ifstream &arch) {
    char coma, nombre[MAX_NOM_ALUMNO];
    // Leer los datos comunes a todos los alumnos
    arch >> coma >> codigo >> coma;
    arch.getline(nombre, MAX_NOM_ALUMNO, ',');
    arch >> escala >> coma >> creditos >> coma;
    // Guardar los datos en el objeto
    SetNombre(nombre);
}

void Alumno::imprime(ofstream &arch) {
    char nombre[MAX_NOM_ALUMNO];
    GetNombre(nombre);
    // Imprimir datos comunes a todos los alumnos
    arch << left << setw(12) << GetCodigo() << setw(MAX_NOM_ALUMNO) << nombre
            << right << setw(4) << GetEscala() << setw(9) << GetCreditos();
}
