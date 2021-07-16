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
    char gravedad[15];
    GetGravedad(gravedad);
    arch << setw(10) << GetCodigo() << setw(15) << gravedad << setw(10) << GetMulta();
    arch << setw(10) << GetDescuento();
}
