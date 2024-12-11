/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: SinReceta.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#include <cstring>
#include "SinReceta.h"
using namespace std;

SinReceta::SinReceta() {
    dni = 0;
    nombre = nullptr;
}

SinReceta::SinReceta(const SinReceta& orig) {
}

SinReceta::~SinReceta() {
    if (nombre) delete nombre;
}

/* Encapsulamiento */

int SinReceta::GetDni() const {
    return dni;
}

void SinReceta::SetDni(int dni) {
    this->dni = dni;
}

void SinReceta::GetNombre(char *nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}

void SinReceta::SetNombre(const char *nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}
