/*
 * Archivo: MuyGrave.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 25 de junio de 2021, 08:54 AM
 */

#include "MuyGrave.h"

MuyGrave::MuyGrave() {
}

MuyGrave::~MuyGrave() {
}

int MuyGrave::GetMeses() const {
    return meses;
}

void MuyGrave::SetMeses(int meses) {
    this->meses = meses;
}

int MuyGrave::GetPuntos() const {
    return puntos;
}

void MuyGrave::SetPuntos(int puntos) {
    this->puntos = puntos;
}
