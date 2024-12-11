/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:19 AM
 */

#include "Escala.h"

Escala::Escala() {
    // No es necesario hacer nada aquí
}

Escala::Escala(const Escala& orig) {
}

Escala::~Escala() {
    // No es necesario hacer nada aquí
}

/* Encapsulamiento */

int Escala::GetCodigo() const {
    return codigo;
}

void Escala::SetCodigo(int codigo) {
    this->codigo = codigo;
}

double Escala::GetPrecio() const {
    return precio;
}

void Escala::SetPrecio(double precio) {
    this->precio = precio;
}
