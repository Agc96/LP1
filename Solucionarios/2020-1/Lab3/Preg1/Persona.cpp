/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Persona.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "Persona.h"

Persona::Persona() {
    inicializar();
}

Persona::Persona(const Persona& orig) {
    inicializar();
}

void Persona::inicializar() {
    this->nombre = nullptr;
    this->distrito = nullptr;
}

Persona::~Persona() {
    if (this->nombre /* != nullptr */) {
        delete this->nombre;
    }
    if (this->distrito /* != nullptr */) {
        delete this->distrito;
    }
}

/* Encapsulamiento */

int Persona::GetCodigo() const {
    return codigo;
}

void Persona::SetCodigo(int codigo) {
    this->codigo = codigo;
}

void Persona::GetDistrito(char* distrito) const {
    if (this->distrito /* != nullptr */) {
        strcpy(distrito, this->distrito);
    } else {
        distrito[0] = '\0';
    }
}

void Persona::SetDistrito(char* distrito) {
    if (this->distrito /* != nullptr */) {
        delete this->distrito;
    }
    this->distrito = new char[strlen(distrito)+1];
    strcpy(this->distrito, distrito);
}

void Persona::GetNombre(char* nombre) const {
    if (this->nombre /* != nullptr */) {
        strcpy(nombre, this->nombre);
    } else {
        nombre[0] = '\0';
    }
}

void Persona::SetNombre(char* nombre) {
    if (this->nombre /* != nullptr */) {
        delete this->nombre;
    }
    this->distrito = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}
