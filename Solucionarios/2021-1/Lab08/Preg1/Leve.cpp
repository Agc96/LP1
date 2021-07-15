/*
 * Archivo: Leve.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#include "Leve.h"

Leve::Leve() {
}

Leve::~Leve() {
}

double Leve::GetDescuento() const {
    return descuento;
}

void Leve::SetDescuento(double descuento) {
    this->descuento = descuento;
}

