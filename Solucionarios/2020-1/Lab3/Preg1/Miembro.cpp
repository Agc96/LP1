/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Miembro.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "Miembro.h"

Miembro::Miembro() {
    this->lalumno = nullptr;
    this->lprofesor = nullptr;
}

Miembro::Miembro(const Miembro& orig) {
    // TODO
}

Miembro::~Miembro() {
    if (this->lalumno /* != nullptr */) {
        delete[] lalumno;
    }
    if (this->lprofesor /* != nullptr */) {
        delete[] lprofesor;
    }
}

/* Lectura e impresión */

istream& Miembro::leer(istream& in) {
    
    return in;
}

ostream& Miembro::imprimir(ostream& out) {
    return out;
}
