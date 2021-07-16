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
    char gravedad[15];
    GetGravedad(gravedad);
    arch << setw(10) << GetCodigo() << setw(15) << gravedad << setw(10) << GetMulta();
    arch << setw(10) << GetPuntos() << setw(10) << GetMeses();
}
