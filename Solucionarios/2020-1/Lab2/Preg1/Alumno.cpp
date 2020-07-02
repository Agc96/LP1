/* 
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <cstring>
#include "Alumno.h"
using namespace std;

Alumno::Alumno() {
    this->codigo = 0;
    this->tipo = '\0';
    this->nombre = nullptr;
    this->numcur = 0;
}

Alumno::Alumno(const Alumno& orig) {
    this->SetNombre(orig.nombre);
    this->SetCodigo(orig.codigo);
    this->SetTipo(orig.tipo);
    this->SetNumcur(orig.numcur);
    for (int i = 0; i < orig.numcur; i++) {
        this->SetLcursoAt(i, orig.lcurso[i]);
    }
}

Alumno::~Alumno() {
    if (this->nombre != nullptr) {
        delete (this->nombre);
    }
}

/* Operadores */

void Alumno::operator +(const ACurso& acurso) {
    /* Validar los datos */
    if (acurso.GetCodigo() != this->GetCodigo()) {
        cerr << "El codigo del alumno y del curso no son iguales." << endl;
        return;
    }
    if (acurso.GetOperacion() != 'N') {
        cerr << "La operacion del alumno-curso no es N (nuevo)." << endl;
        return;
    }
    /* Insertar el curso en la lista del alumno */
    int numcur = this->GetNumcur();
    this->SetLcursoAt(numcur, acurso.GetCurso());
    this->SetNumcur(++numcur);
}

void Alumno::operator *(const ACurso& acurso) {
    /* Validar los datos */
    if (acurso.GetCodigo() != this->GetCodigo()) {
        cerr << "El codigo del alumno y del curso no son iguales." << endl;
        return;
    }
    if (acurso.GetOperacion() != 'A') {
        cerr << "La operacion del alumno-curso no es A (actualizar)." << endl;
        return;
    }
    /* Buscar el curso en la lista del alumno */
    Curso curso = acurso.GetCurso();
    bool encontrado = false;
    for (int i = 0; i < numcur; i++) {
        if (lcurso[i] == curso) {
            lcurso[i].SetNota(curso.GetNota());
            lcurso[i].SetCredito(curso.GetCredito());
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cerr << "No se encontró el curso-ciclo en la lista del alumno." << endl;
    }
}

void Alumno::operator -(const ACurso& acurso) {
    /* Validar los datos */
    if (acurso.GetCodigo() != this->GetCodigo()) {
        cerr << "El codigo del alumno y del curso no son iguales." << endl;
        return;
    }
    if (acurso.GetOperacion() != 'E') {
        cerr << "La operación del alumno-curso no es E (eliminar)." << endl;
        return;
    }
    /* Buscar el curso en la lista del alumno */
    Curso curso = acurso.GetCurso();
    bool encontrado = false;
    for (int i = 0; i < numcur; i++) {
        if (lcurso[i] == curso) {
            for (int j = i; j < numcur - 1; j++) {
                lcurso[j] = lcurso[j + 1];
            }
            --numcur;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cerr << "No se encontró el curso-ciclo en la lista del alumno." << endl;
    }
}

double Alumno::operator /(int ciclo) {
    double suma = 0;
    int cont = 0;
    for (int i = 0; i < numcur; i++) {
        if (lcurso[i].GetCiclo() == ciclo) {
            suma += lcurso[i].GetNota();
            cont++;
        }
    }
    return (cont > 0) ? suma/cont : 0;
}

double Alumno::operator --() {
    double suma = 0;
    for (int i = 0; i < numcur; i++) {
        suma += lcurso[i].GetCredito();
    }
    return suma;
}

double Alumno::operator ++() {
    double suma = 0;
    for (int i = 0; i < numcur; i++) {
        if (lcurso[i].GetNota() >= 11) {
            suma += lcurso[i].GetCredito();
        }
    }
    return suma;
}

/* Encapsulamiento */

int Alumno::GetCodigo() const {
    return codigo;
}

void Alumno::SetCodigo(int codigo) {
    this->codigo = codigo;
}

char Alumno::GetTipo() const {
    return tipo;
}

void Alumno::SetTipo(char tipo) {
    this->tipo = tipo;
}

char* Alumno::GetNombre() const {
    if (nombre == nullptr) {
        return nullptr;
    } else {
        char *copia = new char[strlen(nombre) + 1];
        strcpy(copia, nombre);
        return copia;
    }
}

void Alumno::SetNombre(char* nombre) {
    if (nombre == nullptr) {
        this->nombre = nullptr;
    } else {
        if (this->nombre != nullptr) {
            delete this->nombre;
        }
        this->nombre = new char[strlen(nombre) + 1];
        strcpy(this->nombre, nombre);
    }
}

Curso Alumno::GetLcursoAt(int index) const {
    return lcurso[index];
}

void Alumno::SetLcursoAt(int index, const Curso& curso) {
    lcurso[index] = curso;
}

int Alumno::GetNumcur() const {
    return numcur;
}

void Alumno::SetNumcur(int numcur) {
    this->numcur = numcur;
}
