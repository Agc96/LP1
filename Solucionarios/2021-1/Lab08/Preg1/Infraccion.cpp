/*
 * Archivo: Infraccion.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:51 AM
 */

#include <cstring>
#include "Infraccion.h"
using namespace std;

Infraccion::Infraccion() {
    codigo = 0;
    gravedad = nullptr;
}

Infraccion::~Infraccion() {
    if (gravedad != nullptr) delete gravedad;
}

int Infraccion::GetCodigo() const {
    return codigo;
}

void Infraccion::SetCodigo(int codigo) {
    this->codigo = codigo;
}

char* Infraccion::GetGravedad() const {
    if (gravedad == nullptr) return nullptr;
    char* aux = new char[strlen(gravedad)+1];
    strcpy(aux, gravedad);
    return aux;
}

void Infraccion::SetGravedad(const char* aux) {
    if (gravedad != nullptr) delete gravedad;
    if (aux == nullptr) gravedad == nullptr;
    else {
        gravedad = new char[strlen(aux)+1];
        strcpy(gravedad, aux);
    }
}

double Infraccion::GetMulta() const {
    return multa;
}

void Infraccion::SetMulta(double multa) {
    this->multa = multa;
}
