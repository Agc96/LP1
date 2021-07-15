/*
 * Archivo: Conductor.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:45 AM
 */

#include <cstring>
#include "Conductor.h"
using namespace std;

Conductor::Conductor() {
    nombre = nullptr;
}

Conductor::~Conductor() {
    if (nombre != nullptr) delete nombre;
}

int Conductor::GetLicencia() const {
    return licencia;
}

void Conductor::SetLicencia(int licencia) {
    this->licencia = licencia;
}

char* Conductor::GetNombre() const {
    if (nombre == nullptr) return nullptr;
    char* aux = new char[strlen(nombre)+1];
    strcpy(aux, nombre);
    return aux;
}

void Conductor::SetNombre(const char* aux) {
    if (nombre != nullptr) delete nombre;
    if (aux == nullptr) nombre = nullptr;
    else {
        nombre = new char[strlen(aux)+1];
        strcpy(nombre, aux);
    }
}
