/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:23 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Semipresencial.h"
using namespace std;

Semipresencial::Semipresencial() {
    total = 0;
}

Semipresencial::Semipresencial(const Semipresencial& orig) {
}

Semipresencial::~Semipresencial() {
    // No es necesario hacer nada aquí
}

/* Encapsulamiento */

double Semipresencial::GetDescuento() const {
    return descuento;
}

void Semipresencial::SetDescuento(double descuento) {
    this->descuento = descuento;
}

double Semipresencial::GetTotal() const {
    return total;
}

void Semipresencial::SetTotal(double total) {
    this->total = total;
}

/* Métodos */

void Semipresencial::lee(ifstream &arch) {
    Alumno::lee(arch);
    arch >> descuento;
}

void Semipresencial::actualizatotal(double precio) {
    double monto = GetCreditos() * precio;
    SetTotal(- monto * GetDescuento() / 100);
    Alumno::SetTotal(monto + GetTotal());
}

void Semipresencial::imprime(ofstream &arch) {
    Alumno::imprime(arch);
    arch << setw(22) << Alumno::GetTotal() << endl;
}
