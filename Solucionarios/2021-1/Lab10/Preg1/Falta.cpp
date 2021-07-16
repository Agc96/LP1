/*
 * Archivo: Falta.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:13 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Falta.h"
using namespace std;

Falta::Falta() {
    this->placa = nullptr;
}

Falta::Falta(int licencia, int fecha, const char* placa) {
    this->placa = nullptr;
    SetLicencia(licencia);
    SetFecha(fecha);
    SetPlaca(placa);
}

Falta::~Falta() {
    if (placa) delete placa;
}

int Falta::GetFecha() const {
    return fecha;
}

void Falta::SetFecha(int fecha) {
    this->fecha = fecha;
}

int Falta::GetLicencia() const {
    return licencia;
}

void Falta::SetLicencia(int licencia) {
    this->licencia = licencia;
}

void Falta::GetPlaca(char* placa) const {
    if (this->placa == nullptr) placa[0] = 0;
    else strcpy(placa, this->placa);
}

void Falta::SetPlaca(const char* placa) {
    if (this->placa != nullptr) delete this->placa;
    this->placa = new char[strlen(placa)+1];
    strcpy(this->placa, placa);
}

void Falta::imprimir(ofstream& arch) {
    char placa[10];
    int fecha = GetFecha();
    arch << setfill('0') << setw(4) << (fecha/10000); // aaaa
    arch << '/' << setw(2) << (fecha/100)%100; // mm
    arch << '/' << setw(2) << (fecha%100) << setfill(' '); // dd
    arch << setw(10) << GetLicencia();
    GetPlaca(placa);
    arch << setw(10) << placa;
}
