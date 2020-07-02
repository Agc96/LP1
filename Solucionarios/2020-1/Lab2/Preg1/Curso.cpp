/* 
 * Archivo: Curso.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <cstring>
#include "Curso.h"

Curso::Curso() {
    this->ccurso = nullptr;
    this->ciclo = 0;
    this->nota = 0;
    this->credito = 0;
}

Curso::Curso(const Curso& orig) {
    this->asignar(orig);
}

Curso::~Curso() {
    if (this->ccurso != nullptr) {
        delete this->ccurso;
    }
}

/* Asignación */

const Curso& Curso::asignar(const Curso& orig) {
    // Copiar los datos del curso origen a este objeto
    this->SetCcurso(orig.ccurso);
    this->SetCiclo(orig.ciclo);
    this->SetNota(orig.nota);
    this->SetCredito(orig.credito);
    // Devolver la referencia a este objeto
    return *this;
}

const Curso& Curso::operator =(const Curso& orig) {
    return this->asignar(orig);
}

/* Comparación */

bool Curso::compare(const Curso& other) {
    return (this->ciclo == other.ciclo) && (strcmp(this->ccurso, other.ccurso) == 0);
}

bool Curso::operator ==(const Curso& other) {
    return this->compare(other);
}

/* Encapsulamiento */

char* Curso::GetCcurso() const {
    if (ccurso == nullptr) {
        return nullptr;
    } else {
        char *copia = new char[strlen(ccurso) + 1];
        strcpy(copia, ccurso);
        return copia;
    }
}

void Curso::SetCcurso(char* ccurso) {
    if (ccurso == nullptr) {
        this->ccurso = nullptr;
    } else {
        if (this->ccurso != nullptr) {
            delete this->ccurso;
        }
        this->ccurso = new char[strlen(ccurso) + 1];
        strcpy(this->ccurso, ccurso);
    }
}

int Curso::GetCiclo() const {
    return ciclo;
}

void Curso::SetCiclo(int ciclo) {
    this->ciclo = ciclo;
}

double Curso::GetCredito() const {
    return credito;
}

void Curso::SetCredito(double credito) {
    this->credito = credito;
}

int Curso::GetNota() const {
    return nota;
}

void Curso::SetNota(int nota) {
    this->nota = nota;
}
