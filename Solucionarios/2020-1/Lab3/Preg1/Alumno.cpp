/* 
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <cstring>
#include "Alumno.h"
#define MAX_LINEA 120

Alumno::Alumno() {
    inicializar();
}

Alumno::Alumno(const Alumno& orig) {
    char buffer[MAX_LINEA];
    inicializar();
    // Copiar especialidad
    orig.GetEspecialidad(buffer);
    SetEspecialidad(buffer);
    // Copiar facultad
    orig.GetFacultad(buffer);
    SetFacultad(buffer);
    // Copiar escala
    SetEscala(orig.GetEscala());
}

void Alumno::inicializar() {
    this->especialidad = nullptr;
    this->facultad = nullptr;
}

Alumno::~Alumno() {
    if (this->especialidad) {
        delete this->especialidad;
    }
    if (this->facultad) {
        delete this->facultad;
    }
}

int Alumno::GetEscala() const {
    return escala;
}

void Alumno::SetEscala(int escala) {
    this->escala = escala;
}

void Alumno::GetEspecialidad(char* especialidad) const {
    if (this->especialidad /* != nullptr */) { 
        strcpy(especialidad, this->especialidad);
    } else {
        especialidad[0] = '\0';
    }
}

void Alumno::SetEspecialidad(char* especialidad) {
    if (this->especialidad /* != nullptr */) {
        delete this->especialidad;
    }
    this->especialidad = new char[strlen(especialidad)+1];
    strcpy(this->especialidad, especialidad);
}

void Alumno::GetFacultad(char* facultad) const {
    if (this->facultad /* != nullptr */) {
        strcpy(facultad, this->facultad);
    } else {
        facultad[0] = '\0';
    }
}

void Alumno::SetFacultad(char* facultad) {
    if (this->facultad /* != nullptr */) {
        delete this->facultad;
    }
    this->facultad = new char[strlen(facultad)+1];
    strcpy(this->facultad, facultad);
}
