/*
 * File:   ProductoEntregado.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:33 AM
 */

#include <cstring>
#include "ProductoEntregado.h"
using namespace std;

ProductoEntregado::ProductoEntregado() {
    codigo = nullptr;
}

ProductoEntregado::ProductoEntregado(const ProductoEntregado& orig) {
}

ProductoEntregado::~ProductoEntregado() {
    if (codigo) delete[] codigo;
}

void ProductoEntregado::GetCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void ProductoEntregado::SetCodigo(const char* codigo) {
    if (this->codigo) delete[] this->codigo;
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

double ProductoEntregado::GetPrecio() const {
    return precio;
}

void ProductoEntregado::SetPrecio(double precio) {
    this->precio = precio;
}
