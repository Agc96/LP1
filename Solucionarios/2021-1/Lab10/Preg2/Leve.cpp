/*
 * Archivo: Leve.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Leve.h"
using namespace std;

Leve::Leve() {
}

Leve::Leve(int codigo, const char* gravedad, double multa, double descuento):
        Infraccion(codigo, gravedad, multa) {
    SetDescuento(descuento);
}


Leve::~Leve() {
}

double Leve::GetDescuento() const {
    return descuento;
}

void Leve::SetDescuento(double descuento) {
    this->descuento = descuento;
}

void Leve::imprimir(ofstream& arch) {
    char gravedad[10];
    GetGravedad(gravedad);
    arch << left << setw(4) << ' ' << setw(10) << gravedad;
    arch << right << setw(12) << GetMulta();
    arch << setw(10) << GetDescuento() << setw(10) << 0 << setw(10) << 0;
}
