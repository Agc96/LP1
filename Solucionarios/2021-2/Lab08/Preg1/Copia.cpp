/*
 * File:   Copia.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 21 de noviembre de 2021, 05:49 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Copia.h"
#include "FuncionesFecha.h"
using namespace std;

Copia::Copia() {
    numero = 0;
    estado = nullptr;
}

Copia::Copia(const Copia& orig) {
    estado = nullptr;
    copiar(orig);
}

Copia::~Copia() {
    if (estado) delete estado;
}

/* Métodos */

void Copia::leer(ifstream& arch) {
    char c;
    int zona;
    // Leer los datos del archivo
    Libro::leer(arch);
    arch >> c >> zona >> ws;
    // Colocar los datos en el objeto
    SetNumero(1);
    SetEstado("Disponible");
    Odisponible.SetZona(zona);
}

void Copia::copiar(const Copia& orig) {
    char estado[20];
    Libro::copiar(orig);
    SetNumero(orig.GetNumero());
    orig.GetEstado(estado);
    SetEstado(estado);
    Odisponible.SetZona(orig.Odisponible.GetZona());
    Oprestamo.SetDias(orig.Oprestamo.GetDias());
    Oprestamo.SetFecha(orig.Oprestamo.GetFecha());
    Operdida.SetPrecio(orig.Operdida.GetPrecio());
}

void Copia::actualizar(int hoy, int fecha) {
    int dias = numeroDeDias(hoy, fecha);
    if (dias >= 60) {
        SetEstado("Perdida");
        Operdida.SetPrecio(this->getPrecio());
    } else {
        SetEstado("Prestamo");
        Oprestamo.SetDias(dias);
        Oprestamo.SetFecha(fecha);
    }
    Odisponible.SetZona(0);
}

void Copia::imprimir(ofstream& arch, bool lineaInicial) {
    char estado[20];
    // Imprimir datos generales del libro
    if (GetNumero() == 1) {
        Libro::imprimir(arch, lineaInicial);
    }
    // Imprimir datos de cada copia del libro
    GetEstado(estado);
    arch << left << setw(5) << GetNumero() << setw(20) << estado;
    if (strcmp(estado, "Disponible") == 0) {
        arch << right << "Zona: " << setw(12) << Odisponible.GetZona() << endl;
    } else if (strcmp(estado, "Perdida") == 0) {
        arch << right << "Precio: " << setw(10) << Operdida.GetPrecio() << endl;
    } else {
        arch << right << "Dias: " << setw(12) << Oprestamo.GetDias() << endl;
    }
}

/* Encapsulamiento */

void Copia::GetEstado(char* estado) const {
    if (this->estado) strcpy(estado, this->estado);
    else estado[0] = 0;
}

void Copia::SetEstado(const char* estado) {
    if (this->estado) delete this->estado;
    this->estado = new char[strlen(estado) + 1];
    strcpy(this->estado, estado);
}

int Copia::GetNumero() const {
    return numero;
}

void Copia::SetNumero(int numero) {
    this->numero = numero;
}
