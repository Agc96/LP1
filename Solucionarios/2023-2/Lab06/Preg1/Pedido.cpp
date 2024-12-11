/*
 * File:   Pedido.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#include <cstring>
#include "Pedido.h"
using namespace std;

Pedido::Pedido() {
    codigo = nullptr;
}

Pedido::Pedido(const Pedido& orig) {
}

Pedido::~Pedido() {
    if (codigo) delete[] codigo;
}

void Pedido::GetCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void Pedido::SetCodigo(const char* codigo) {
    if (this->codigo) delete[] this->codigo;
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

int Pedido::GetDniCliente() const {
    return dni_cliente;
}

void Pedido::SetDniCliente(int dni_cliente) {
    this->dni_cliente = dni_cliente;
}

double Pedido::GetPrecioProducto() const {
    return precio_producto;
}

void Pedido::SetPrecioProducto(double precio_producto) {
    this->precio_producto = precio_producto;
}

/* Lectura */

bool operator >>(ifstream &arch, Pedido &pedido) {
    char codigo[MAX_COD_PROD];
    int dni;
    arch.getline(codigo, MAX_COD_PROD, ',');
    if (arch.eof()) return false;
    arch >> dni >> ws;
    pedido.SetCodigo(codigo);
    pedido.SetDniCliente(dni);
    return true;
}
