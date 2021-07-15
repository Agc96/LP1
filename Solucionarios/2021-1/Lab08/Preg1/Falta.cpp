/*
 * Archivo: Falta.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:50 AM
 */

#include <cstring>
#include "Falta.h"
using namespace std;

Falta::Falta() {
    placa = nullptr;
}

Falta::Falta(const Falta& orig) {
}

Falta::~Falta() {
    if (placa != nullptr) delete placa;
}

int Falta::GetFecha() const {
    return fecha;
}

void Falta::SetFecha(int fecha) {
    this->fecha = fecha;
}

char* Falta::GetPlaca() const {
    if (placa == nullptr) return nullptr;
    char* aux = new char[strlen(placa)+1];
    strcpy(aux, placa);
    return aux;
}

void Falta::SetPlaca(const char* aux) {
    if (placa != nullptr) delete placa;
    if (aux == nullptr) placa = nullptr;
    else {
        placa = new char[strlen(aux)+1];
        strcpy(placa, aux);
    }
}