/*
 * File:   Cliente.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:36 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Cliente.h"
using namespace std;

#define MAX_NOM_CLI 50

Cliente::Cliente() {
    dni = 0;
    nombre = nullptr;
    cantidad_productos_entregados = 0;
    monto_total = 0;
}

Cliente::Cliente(const Cliente& orig) {
}

Cliente::~Cliente() {
    if (nombre) delete[] nombre;
}

/* Encapsulamiento */

int Cliente::GetDni() const {
    return dni;
}

void Cliente::SetDni(int dni) {
    this->dni = dni;
}

double Cliente::GetMontoTotal() const {
    return monto_total;
}

void Cliente::SetMontoTotal(double monto_total) {
    this->monto_total = monto_total;
}

void Cliente::GetNombre(char* nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}

void Cliente::SetNombre(const char* nombre) {
    if (this->nombre) delete[] this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}

int Cliente::GetTelefono() const {
    return telefono;
}

void Cliente::SetTelefono(int telefono) {
    this->telefono = telefono;
}

int Cliente::GetCantidadProductosEntregados() const {
    return cantidad_productos_entregados;
}

/* Agregación */

void Cliente::operator +=(Pedido &pedido) {
    char codigo[MAX_COD_PROD]{};
    double precio = pedido.GetPrecioProducto();
    pedido.GetCodigo(codigo);
    productos_entregados[cantidad_productos_entregados].SetCodigo(codigo);
    productos_entregados[cantidad_productos_entregados].SetPrecio(precio);
    monto_total += precio;
    cantidad_productos_entregados++;
}

/* Lectura e impresión */

bool operator >>(ifstream &arch, Cliente &cliente) {
    int dni, telefono;
    char nombre[MAX_NOM_CLI]{}, coma;
    arch >> dni >> coma;
    if (arch.eof()) return false;
    arch.getline(nombre, MAX_NOM_CLI, ',');
    arch >> telefono >> ws;
    cliente.SetDni(dni);
    cliente.SetNombre(nombre);
    cliente.SetTelefono(telefono);
    return true;
}

void operator <<(ofstream &arch, Cliente &cliente) {
    char nombre[MAX_NOM_CLI]{};
    cliente.GetNombre(nombre);
    arch << left << setw(10) << cliente.GetDni()
            << setw(MAX_NOM_CLI) << nombre
            << right << setw(9)<< cliente.GetTelefono()
            << setw(11) << cliente.GetMontoTotal();
    cliente.imprimirListaProductos(arch);
    arch << endl;
}

/* Métodos */

void Cliente::imprimirListaProductos(ofstream &arch) {
    char codProd[MAX_COD_PROD]{};
    arch << setw(4) << ' ';
    if (cantidad_productos_entregados > 0) {
        arch << "Productos entregados:";
        for (int i = 0; i < cantidad_productos_entregados; i++) {
            productos_entregados[i].GetCodigo(codProd);
            arch << right << setw(MAX_COD_PROD) << codProd;
        }
    } else {
        arch << "NO SE LE ENTREGARON PRODUCTOS";
    }
}
