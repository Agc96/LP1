/* 
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <cstring>
#include "Alumno.h"

Alumno::Alumno() {
    inicializar();
}

Alumno::Alumno(const Alumno& orig) {
    inicializar();
    *this = orig;
}

void Alumno::inicializar() {
    especialidad = nullptr;
    facultad = nullptr;
}

Alumno::~Alumno() {
    if (especialidad) delete especialidad;
    if (facultad) delete facultad;
}

/* Operadores sobrecargados */

Alumno& Alumno::operator =(const Alumno& right) {
    // Verificar que el objeto de la derecha no sea este mismo objeto
    if (this == &right) return *this;
    // Copiar los datos del objeto de la derecha
    Persona::operator =(right);
    SetEscala(right.escala);
    SetEspecialidad(right.especialidad);
    SetFacultad(right.facultad);
    return *this;
}

/* Lectura e impresión de datos */

istream& Alumno::leer(istream& in) {
    char buffer[MAX_LINEA], c;
    // Leer los datos principales (Persona)
    Persona::leer(in);
    // Leer la escala del alumno
    in >> escala >> c;
    // Leer la especialidad del alumno
    in.getline(buffer, MAX_LINEA, ',');
    SetEspecialidad(buffer);
    // Leer la facultad del alumno
    in.getline(buffer, MAX_LINEA);
    SetFacultad(buffer);
    return in;
}

ostream& Alumno::imprimir(ostream& out) {
    Persona::imprimir(out);
    out << "Escala: " << escala << endl;
    out << "Especialidad: " << especialidad << endl;
    out << "Facultad: " << facultad << endl;
    return out;
}

/* Encapsulamiento */

int Alumno::GetEscala() const {
    return escala;
}

void Alumno::SetEscala(int escala) {
    this->escala = escala;
}

char* Alumno::GetEspecialidad() const {
    return crearCadena(this->especialidad);
}

void Alumno::SetEspecialidad(char* especialidad) {
    if (this->especialidad) delete this->especialidad;
    this->especialidad = crearCadena(especialidad);
}

char* Alumno::GetFacultad() const {
    return crearCadena(this->facultad);
}

void Alumno::SetFacultad(char* facultad) {
    if (this->facultad) delete this->facultad;
    this->facultad = crearCadena(facultad);
}
