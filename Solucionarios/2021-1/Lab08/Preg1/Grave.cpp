/*
 * Archivo: Grave.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#include "Grave.h"

Grave::Grave() {
}

Grave::~Grave() {
}

double Grave::GetDescuento() const {
    return descuento;
}

void Grave::SetDescuento(double descuento) {
    this->descuento = descuento;
}

int Grave::GetPuntos() const {
    return puntos;
}

void Grave::SetPuntos(int puntos) {
    this->puntos = puntos;
}
