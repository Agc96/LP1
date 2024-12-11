/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Medico.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Medico.h"
using namespace std;

Medico::Medico() {
    codigo = 0;
    nombre = nullptr;
    especialidad = nullptr;
}

Medico::Medico(const Medico& orig) {
    // No se usará
}

Medico::~Medico() {
    if (nombre) delete nombre;
    if (especialidad) delete especialidad;
}

/* Métodos */

void Medico::leer(ifstream &arch) {
    char buffer[50];
    int codigo;
    arch >> codigo;
    if (arch.eof()) return;
    SetCodigo(codigo);
    arch.get();
    arch.getline(buffer, 50, ',');
    SetNombre(buffer);
    arch.getline(buffer, 50);
    SetEspecialidad(buffer);
}

/* Encapsulamiento */

int Medico::GetCodigo() const {
    return codigo;
}

void Medico::SetCodigo(int codigo) {
    this->codigo = codigo;
}

void Medico::GetEspecialidad(char *especialidad) const {
    if (this->especialidad) strcpy(especialidad, this->especialidad);
    else especialidad[0] = 0;
}

void Medico::SetEspecialidad(const char *especialidad) {
    if (this->especialidad) delete this->especialidad;
    this->especialidad = new char[strlen(especialidad)+1];
    strcpy(this->especialidad, especialidad);
}

void Medico::GetNombre(char *nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}

void Medico::SetNombre(const char *nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}
