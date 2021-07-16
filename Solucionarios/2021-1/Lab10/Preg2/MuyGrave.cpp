/*
 * Archivo: MuyGrave.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "MuyGrave.h"
using namespace std;

MuyGrave::MuyGrave() {
}

MuyGrave::MuyGrave(int codigo, const char* gravedad, double multa, int puntos, int meses):
        Infraccion(codigo, gravedad, multa) {
    SetPuntos(puntos);
    SetMeses(meses);
}

MuyGrave::~MuyGrave() {
}

int MuyGrave::GetMeses() const {
    return meses;
}

void MuyGrave::SetMeses(int meses) {
    this->meses = meses;
}

int MuyGrave::GetPuntos() const {
    return puntos;
}

void MuyGrave::SetPuntos(int puntos) {
    this->puntos = puntos;
}

void MuyGrave::imprimir(ofstream& arch) {
    char gravedad[10];
    GetGravedad(gravedad);
    arch << left << setw(4) << ' ' << setw(10) << gravedad;
    arch << right << setw(12) << GetMulta();
    arch << setw(10) << 0.0 << setw(10) << GetPuntos() << setw(10) << GetMeses();
}
