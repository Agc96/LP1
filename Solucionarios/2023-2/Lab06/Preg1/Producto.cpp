/*
 * File:   Producto.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 27 de octubre de 2023, 09:42 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Producto.h"
using namespace std;

#define MAX_DESC_PROD 60

Producto::Producto() {
    codigo = nullptr;
    descripcion = nullptr;
    cantidad_clientes_servidos = 0;
    cantidad_clientes_no_servidos = 0;
}

Producto::Producto(const Producto& orig) {
}

Producto::~Producto() {
    if (codigo) delete[] codigo;
    if (descripcion) delete[] descripcion;
}

void Producto::GetCodigo(char* codigo) const {
    if (this->codigo) strcpy(codigo, this->codigo);
    else codigo[0] = 0;
}

void Producto::SetCodigo(const char* codigo) {
    if (this->codigo) delete[] this->codigo;
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

void Producto::GetDescripcion(char* descripcion) const {
    if (this->descripcion) strcpy(descripcion, this->descripcion);
    else descripcion[0] = 0;
}

void Producto::SetDescripcion(const char* descripcion) {
    if (this->descripcion) delete[] this->descripcion;
    this->descripcion = new char[strlen(descripcion)+1];
    strcpy(this->descripcion, descripcion);
}

double Producto::GetPrecio() const {
    return precio;
}

void Producto::SetPrecio(double precio) {
    this->precio = precio;
}

int Producto::GetStock() const {
    return stock;
}

void Producto::SetStock(int stock) {
    this->stock = stock;
}

int Producto::GetCantidadClientesNoServidos() const {
    return cantidad_clientes_no_servidos;
}

int Producto::GetCantidadClientesServidos() const {
    return cantidad_clientes_servidos;
}

/* Agregación */

bool Producto::operator +=(Pedido &pedido) {
    int dni = pedido.GetDniCliente();
    pedido.SetPrecioProducto(GetPrecio());
    if (stock > 0) {
        clientes_servidos[cantidad_clientes_servidos] = dni;
        cantidad_clientes_servidos++;
        stock--;
        return true;
    }
    clientes_no_servidos[cantidad_clientes_no_servidos] = dni;
    cantidad_clientes_no_servidos++;
    return false;
}

/* Lectura e impresión */

bool operator >>(ifstream &arch, Producto &producto) {
    char codigo[MAX_COD_PROD], descripcion[MAX_DESC_PROD], coma;
    double precio;
    int stock;
    arch.getline(codigo, MAX_COD_PROD, ',');
    if (arch.eof()) return false;
    arch.getline(descripcion, MAX_DESC_PROD, ',');
    arch >> precio >> coma >> stock >> ws;
    producto.SetCodigo(codigo);
    producto.SetDescripcion(descripcion);
    producto.SetPrecio(precio);
    producto.SetStock(stock);
    return true;
}

void operator <<(ofstream &arch, Producto &producto) {
    char codigo[MAX_COD_PROD]{}, descripcion[MAX_DESC_PROD]{};
    producto.GetCodigo(codigo);
    producto.GetDescripcion(descripcion);
    arch << left << setw(MAX_COD_PROD) << codigo
            << setw(MAX_DESC_PROD) << descripcion
            << right << setw(10) << producto.GetPrecio()
            << setw(10) << producto.GetStock() << endl;
    producto.imprimirListaClientes(arch);
}

/* Métodos adicionales */

void Producto::imprimirListaClientes(ofstream &arch) {
    // Imprimir lista de clientes atendidos
    if (cantidad_clientes_servidos > 0) {
        arch << left << setw(22) << "Clientes atendidos:";
        for (int i = 0; i < cantidad_clientes_servidos; i++) {
            arch << right << setw(10) << clientes_servidos[i];
        }
    } else {
        arch << "NO SE ATENDIERON PEDIDOS";
    }
    arch << endl;
    // Imprimir lista de clientes no atendidos
    if (cantidad_clientes_no_servidos > 0) {
        arch << left << setw(22) << "Clientes no atendidos:";
        for (int i = 0; i < cantidad_clientes_no_servidos; i++) {
            arch << right << setw(10) << clientes_no_servidos[i];
        }
    } else {
        arch << "NO HAY CLIENTES SIN ATENDER";
    }
    arch << endl;
}
