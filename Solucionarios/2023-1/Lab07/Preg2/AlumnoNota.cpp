/*
 * Archivo: AlumnoNota.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:15 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Constantes.h"
#include "AlumnoNota.h"
using namespace std;

AlumnoNota::AlumnoNota() {
    codigo = 0;
    codcurso = nullptr;
}

AlumnoNota::AlumnoNota(const AlumnoNota& orig) {
    // No se está utilizando para la solución del problema.
}

AlumnoNota::~AlumnoNota() {
    if (codcurso) delete[] codcurso;
}

/* Encapsulamiento */

int AlumnoNota::GetCiclo() const {
    return ciclo;
}

void AlumnoNota::SetCiclo(int ciclo) {
    this->ciclo = ciclo;
}

void AlumnoNota::GetCodCurso(char *cadena) const {
    if (cadena == nullptr) return;
    if (codcurso) strcpy(cadena, codcurso);
    else cadena[0] = 0;
}

void AlumnoNota::SetCodCurso(const char *cadena) {
    if (cadena == nullptr) return;
    if (codcurso) delete[] codcurso;
    codcurso = new char[strlen(cadena)+1];
    strcpy(codcurso, cadena);
}

int AlumnoNota::GetCodigo() const {
    return codigo;
}

void AlumnoNota::SetCodigo(int codigo) {
    this->codigo = codigo;
}

int AlumnoNota::GetNota() const {
    return nota;
}

void AlumnoNota::SetNota(int nota) {
    this->nota = nota;
}

/* Sobrecargas */

ifstream& operator >>(ifstream &arch, AlumnoNota &alumnoNota) {
    int codigo, ciclo, nota;
    char curso[MAX_CURSO], car;
    // Leer la línea del archivo
    arch >> codigo >> car;
    if (arch.eof()) return arch;
    arch.getline(curso, MAX_CURSO, ',');
    arch >> ciclo >> car >> nota;
    // Guardar datos en el objeto
    alumnoNota.SetCodigo(codigo);
    alumnoNota.SetCodCurso(curso);
    alumnoNota.SetCiclo(ciclo);
    alumnoNota.SetNota(nota);
    return arch;
}

void AlumnoNota::operator &(Nota &nota) {
    char curso[MAX_CURSO];
    GetCodCurso(curso);
    nota.SetCodCurso(curso);
    nota.SetCiclo(GetCiclo());
    nota.SetNota(GetNota());
}
