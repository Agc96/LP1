/*
 * File:   Perdida.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 23 de noviembre de 2021, 12:07 AM
 */

#include "Perdida.h"

Perdida::Perdida() {
    precio = 0;
}

Perdida::Perdida(const Perdida& orig) {
}

Perdida::~Perdida() {
}

double Perdida::GetPrecio() const {
    return precio;
}

void Perdida::SetPrecio(double precio) {
    this->precio = precio;
}
