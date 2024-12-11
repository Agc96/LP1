/*
 * Archivo: Nota.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:16 AM
 */

#include <cstring>
#include "Nota.h"
using namespace std;

Nota::Nota() {
    codcurso = nullptr;
}

Nota::Nota(const Nota& orig) {
    // No se está utilizando para la solución del problema.
}

Nota::~Nota() {
    if (codcurso) delete[] codcurso;
}

/* Encapsulamiento */

int Nota::GetCiclo() const {
    return ciclo;
}

void Nota::SetCiclo(int ciclo) {
    this->ciclo = ciclo;
}

void Nota::GetCodCurso(char *cadena) const {
    if (cadena == nullptr) return;
    if (codcurso) strcpy(cadena, codcurso);
    else cadena[0] = 0;
}

void Nota::SetCodCurso(const char *cadena) {
    if (cadena == nullptr) return;
    if (codcurso) delete[] codcurso;
    codcurso = new char[strlen(cadena)+1];
    strcpy(codcurso, cadena);
}

int Nota::GetNota() const {
    return nota;
}

void Nota::SetNota(int nota) {
    this->nota = nota;
}
