/* 
 * Archivo: Nota.cpp
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 29 de noviembre de 2019, 11:26 AM
 */

#include "Nota.h"
#include <cstring>
using namespace std;

Nota::Nota() {
    codigo = nullptr;
    nota = 0;
    semestre = nullptr;
}

Nota::Nota(const Nota& orig) {
    codigo = copia(orig.codigo);
    nota = nota;
    semestre = copia(orig.semestre);
}

Nota::~Nota() {
    if (codigo) delete[] codigo;
    if (semestre) delete[] semestre;
}

char* Nota::getCodigo() {
    return copia(codigo);
}

void Nota::setCodigo(char* codigo) {
    this->codigo = copia(codigo);
}

int Nota::getNota() {
    return nota;
}

void Nota::setNota(int nota) {
    this->nota = nota;
}

char* Nota::getSemestre() {
    return copia(semestre);
}

void Nota::setSemestre(char* semestre) {
    this->semestre = copia(semestre);
}

char* Nota::copia(char* cadena) {
    if (!cadena) return nullptr;
    // Copiar datos de la cadena
    char* nuevaCadena = new char[strlen(cadena) + 1];
    strcpy(nuevaCadena, cadena);
    return nuevaCadena;
}
