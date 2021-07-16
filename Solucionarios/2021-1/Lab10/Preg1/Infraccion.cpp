/*
 * Archivo: Infraccion.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:11 AM
 */

#include <cstring>
#include "Infraccion.h"
using namespace std;

Infraccion::Infraccion() {
    this->gravedad = nullptr;
}

Infraccion::Infraccion(int codigo, const char* gravedad, double multa) {
    this->gravedad = nullptr;
    SetCodigo(codigo);
    SetGravedad(gravedad);
    SetMulta(multa);
}

Infraccion::~Infraccion() {
    if (gravedad) delete gravedad;
}

int Infraccion::GetCodigo() const {
    return codigo;
}

void Infraccion::SetCodigo(int codigo) {
    this->codigo = codigo;
}

void Infraccion::GetGravedad(char* gravedad) {
    if (this->gravedad == nullptr) gravedad[0] = 0;
    else strcpy(gravedad, this->gravedad);
}

void Infraccion::SetGravedad(const char* gravedad) {
    if (this->gravedad != nullptr) delete this->gravedad;
    this->gravedad = new char[strlen(gravedad)+1];
    strcpy(this->gravedad, gravedad);
}

double Infraccion::GetMulta() const {
    return multa;
}

void Infraccion::SetMulta(double multa) {
    this->multa = multa;
}
