/*
 * Archivo: Emergencia.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Emergencia.h"
using namespace std;

Emergencia::Emergencia() : Paciente() {
    nombreRef = nullptr;
}

Emergencia::Emergencia(const Emergencia& orig) : Paciente(orig) {
    nombreRef = nullptr;
    setTelefonoRef(orig.telefonoRef);
    setNombreRef(orig.nombreRef);
}

Emergencia::~Emergencia() {
    if (nombreRef) delete nombreRef;
}

/* Métodos */

int Emergencia::orden() {
    return 3;
}

bool Emergencia::seguro() {
    return false;
}

istream& Emergencia::leer(istream& in) {
    char nombreRef[30];
    int telefonoRef;
    Paciente::leer(in);
    // Leer el nombre de la persona de referencia
    in.getline(nombreRef, 30, ',');
    setNombreRef(nombreRef);
    // Leer el porcentaje del seguro
    in >> telefonoRef;
    in.get();
    setTelefonoRef(telefonoRef);
    return in;
}

ostream& Emergencia::imprimir(ostream& out) {
    Paciente::imprimir(out);
    char* nombreRef = getNombreRef();
    out << left << setw(30) << nombreRef << setw(4) << ' ';
    out << right << setw(10) << getTelefonoRef() << endl;
    delete nombreRef;
    return out;
}

/* Encapsulamiento */

char* Emergencia::getNombreRef() const {
    char* cad = nullptr;
    if (nombreRef) {
        cad = new char[strlen(nombreRef)+1];
        strcpy(cad, nombreRef);
    }
    return cad;
}

void Emergencia::setNombreRef(char* cad) {
    if (nombreRef) delete nombreRef;
    nombreRef = new char[strlen(cad)+1];
    strcpy(nombreRef, cad);
}

int Emergencia::getTelefonoRef() const {
    return telefonoRef;
}

void Emergencia::setTelefonoRef(int telefonoRef) {
    this->telefonoRef = telefonoRef;
}
