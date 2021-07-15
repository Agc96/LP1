/*
 * Archivo: Paciente.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Paciente.h"
using namespace std;

Paciente::Paciente() {
    nombre = nullptr;
}

Paciente::Paciente(const Paciente& orig) {
    nombre = nullptr;
    // Copiar el nombre del paciente
    char* origNombre = orig.getNombre();
    setNombre(origNombre);
    delete origNombre;
    // Copiar los otros atributos
    setDni(orig.getDni());
    setCodMed(orig.getCodMed());
}

Paciente::~Paciente() {
    if (nombre) delete nombre;
}

/* Métodos */

istream& Paciente::leer(istream& in) {
    char nombre[50], c;
    int dni, codMed;
    // Leer el DNI del paciente
    in >> dni;
    in.get();
    setDni(dni);
    // Leer el nombre del paciente
    in.getline(nombre, 50, ',');
    setNombre(nombre);
    // Leer el código del médico
    in >> codMed;
    in.get();
    setCodMed(codMed);
    return in;
}

ostream& Paciente::imprimir(ostream& out) {
    char* nombre = getNombre();
    out << right << setw(8) << getDni() << setw(4) << ' ';
    out << left << setw(50) << nombre << setw(4) << ' ';
    out << right << setw(6) << getCodMed() << setw(4) << ' ';
    delete nombre;
    return out;
}

/* Encapsulamiento */

int Paciente::getCodMed() const {
    return codMed;
}

void Paciente::setCodMed(int codMed) {
    this->codMed = codMed;
}

int Paciente::getDni() const {
    return dni;
}

void Paciente::setDni(int dni) {
    this->dni = dni;
}

char* Paciente::getNombre() const {
    char* cad = nullptr;
    if (nombre) {
        cad = new char[strlen(nombre)+1];
        strcpy(cad, nombre);
    }
    return cad;
}

void Paciente::setNombre(char* cadena) {
    if (nombre) delete nombre;
    nombre = new char[strlen(cadena)+1];
    strcpy(nombre, cadena);
}
