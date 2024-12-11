/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 12:16 AM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Constantes.h"
#include "Alumno.h"
using namespace std;

Alumno::Alumno() {
    codigo = 0;
    nombre = nullptr;
    numcursos = numaprobados = numprimera = numsegunda = numtercera = 0;
}

Alumno::Alumno(const Alumno& orig) {
    // No se está utilizando para la solución del problema.
}

Alumno::~Alumno() {
    if (nombre) delete[] nombre;
}

/* Encapsulamiento */

int Alumno::GetCodigo() const {
    return codigo;
}

void Alumno::SetCodigo(int codigo) {
    this->codigo = codigo;
}

void Alumno::GetNombre(char *cadena) const {
    if (cadena == nullptr) return;
    if (nombre) strcpy(cadena, nombre);
    else cadena[0] = 0;
}

void Alumno::SetNombre(const char *cadena) {
    if (cadena == nullptr) return;
    if (nombre) delete[] nombre;
    nombre = new char[strlen(cadena)+1];
    strcpy(nombre, cadena);
}

int Alumno::GetNumAprobados() const {
    return numaprobados;
}

void Alumno::SetNumAprobados(int numaprobados) {
    this->numaprobados = numaprobados;
}

int Alumno::GetNumCursos() const {
    return numcursos;
}

void Alumno::SetNumCursos(int numcursos) {
    this->numcursos = numcursos;
}

int Alumno::GetNumPrimera() const {
    return numprimera;
}

void Alumno::SetNumPrimera(int numprimera) {
    this->numprimera = numprimera;
}

int Alumno::GetNumSegunda() const {
    return numsegunda;
}

void Alumno::SetNumSegunda(int numsegunda) {
    this->numsegunda = numsegunda;
}

int Alumno::GetNumTercera() const {
    return numtercera;
}

void Alumno::SetNumTercera(int numtercera) {
    this->numtercera = numtercera;
}

/* Sobrecargas */

ifstream& operator >>(ifstream &arch, Alumno &alumno) {
    int codigo;
    char nombre[MAX_NOMBRE], car;
    // Leer la línea del archivo
    arch >> codigo >> car;
    if (arch.eof()) return arch;
    arch.getline(nombre, MAX_NOMBRE, ',');
    while (arch.get() != '\n'); // Ignorar el resto de la línea
    // Guardar datos en el objeto
    alumno.SetCodigo(codigo);
    alumno.SetNombre(nombre);
    return arch;
}

void Alumno::operator +=(Nota &nota) {
    char curso[MAX_CURSO];
    int numnotas = 0;
    // Obtener la cantidad de notas
    while (true) {
        lnotas[numnotas].GetCodCurso(curso);
        if (curso[0] == 0) break;
        numnotas++;
    }
    // Colocar la nueva nota al final del arreglo
    nota.GetCodCurso(curso);
    lnotas[numnotas].SetCodCurso(curso);
    lnotas[numnotas].SetCiclo(nota.GetCiclo());
    lnotas[numnotas].SetNota(nota.GetNota());
}

ofstream& operator <<(ofstream &arch, Alumno &alumno) {
    char nombre[MAX_NOMBRE];
    alumno.GetNombre(nombre);
    arch << "Codigo del Alumno: " << alumno.GetCodigo() << endl;
    arch << "Nombre del Alumno: " << nombre << endl;
    arch << "Detalle de Cursos:" << endl;
    arch << left << setw(10) << "Cursados" << setw(11) << "Aprobados" << setw(9)
            << "1ra Vez" << setw(9) << "2da Vez" << "3ra Vez" << endl;
    arch << right << setw(5) << alumno.GetNumCursos() << setw(10)
            << alumno.GetNumAprobados() << setw(10) << alumno.GetNumPrimera()
            << setw(9) << alumno.GetNumSegunda() << setw(9)
            << alumno.GetNumTercera() << endl;
    return arch;
}
