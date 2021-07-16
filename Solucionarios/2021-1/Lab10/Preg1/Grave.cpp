/*
 * Archivo: Grave.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grave.h"
using namespace std;

Grave::Grave() {
}

Grave::Grave(int codigo, const char* gravedad, double multa, double descuento, int puntos):
        Infraccion(codigo, gravedad, multa) {
    SetDescuento(descuento);
    SetPuntos(puntos);
}


Grave::~Grave() {
}

double Grave::GetDescuento() const {
    return descuento;
}

void Grave::SetDescuento(double descuento) {
    this->descuento = descuento;
}

int Grave::GetPuntos() const {
    return puntos;
}

void Grave::SetPuntos(int puntos) {
    this->puntos = puntos;
}

void Grave::imprimir(ofstream& arch) {
    char gravedad[15];
    GetGravedad(gravedad);
    arch << setw(10) << GetCodigo() << setw(15) << gravedad << setw(10) << GetMulta();
    arch << setw(10) << GetDescuento() << setw(10) << GetPuntos();
}
