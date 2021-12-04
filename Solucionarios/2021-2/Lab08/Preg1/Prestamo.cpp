/*
 * File:   Prestamo.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 23 de noviembre de 2021, 12:07 AM
 */

#include "Prestamo.h"

Prestamo::Prestamo() {
    dias = 0;
    fecha = 0;
}

Prestamo::Prestamo(const Prestamo& orig) {
}

Prestamo::~Prestamo() {
}

int Prestamo::GetDias() const {
    return dias;
}

void Prestamo::SetDias(int dias) {
    this->dias = dias;
}

int Prestamo::GetFecha() const {
    return fecha;
}

void Prestamo::SetFecha(int fecha) {
    this->fecha = fecha;
}
