/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: ConReceta.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#include <cstring>
#include "ConReceta.h"
using namespace std;

ConReceta::ConReceta() {
    codmed = 0;
    especialidad = nullptr;
}

ConReceta::ConReceta(const ConReceta& orig) {
}

ConReceta::~ConReceta() {
    if (especialidad) delete especialidad;
}

// Encapsulamiento

int ConReceta::GetCodmed() const {
    return codmed;
}

void ConReceta::SetCodmed(int codmed) {
    this->codmed = codmed;
}

void ConReceta::GetEspecialidad(char *especialidad) const {
    if (this->especialidad) strcpy(especialidad, this->especialidad);
    else especialidad[0] = 0;
}

void ConReceta::SetEspecialidad(const char *especialidad) {
    if (this->especialidad) delete this->especialidad;
    this->especialidad = new char[strlen(especialidad)+1];
    strcpy(this->especialidad, especialidad);
}
