/*
 * File:   Disponible.cpp
 * Author: Anthony Gutiérrez
 * 
 * Created on 23 de noviembre de 2021, 12:06 AM
 */

#include "Disponible.h"

Disponible::Disponible() {
    zona = 0;
}

Disponible::Disponible(const Disponible& orig) {
}

Disponible::~Disponible() {
}

int Disponible::GetZona() const {
    return zona;
}

void Disponible::SetZona(int zona) {
    this->zona = zona;
}
