/*
 * Archivo: Pedido.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de junio de 2022, 01:58 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Pedido.h"
using namespace std;

Pedido::Pedido() {
    codigo = 0;
    total = 0;
    obs = nullptr;
}

Pedido::Pedido(const Pedido& orig) {
    cerr << "Constructor copia de Pedido" << endl;
}

Pedido::~Pedido() {
    if (obs) delete obs;
}

/* Métodos */

void Pedido::leerPedido(ifstream& arch) {
    int dd, mm, aaaa;
    char c;
    arch >> codigo;
    if (arch.eof()) return;
    arch >> c >> cantidad >> c >> dni >> c >> dd >> c >> mm >> c >> aaaa;
    fecha = 10000*aaaa + 100*mm + dd;
}

void Pedido::imprimirPedido(ofstream& arch) {
    char nombre[50], obs[50];
    getNombre(nombre);
    getObs(obs);
    imprimirFecha(arch);
    arch << left << setw(2) << ' ' << setw(8) << codigo << setw(50) << nombre
            << right << setw(5) << cantidad << setw(8) << getPrecio()
            << setw(9) << total << setw(2) << ' ' << obs << endl;
}

/* Métodos auxiliares */

void Pedido::imprimirFecha(ofstream& arch) {
    int dd = fecha % 100, mm = (fecha / 100) % 100, aaaa = fecha / 10000;
    arch << right << setw(2) << setfill('0') << dd << '/' << setw(2) << mm << '/'
            << setw(4) << aaaa << setfill(' ');
}

/* Encapsulamiento */

int Pedido::getCantidad() const {
    return cantidad;
}
void Pedido::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

int Pedido::getCodigo() const {
    return codigo;
}
void Pedido::setCodigo(int codigo) {
    this->codigo = codigo;
}

int Pedido::getDni() const {
    return dni;
}
void Pedido::setDni(int dni) {
    this->dni = dni;
}

int Pedido::getFecha() const {
    return fecha;
}
void Pedido::setFecha(int fecha) {
    this->fecha = fecha;
}

void Pedido::getObs(char *obs) const {
    if (this->obs) strcpy(obs, this->obs);
    else obs[0] = 0;
}
void Pedido::setObs(const char* obs) {
    if (this->obs) delete this->obs;
    this->obs = new char[strlen(obs)+1];
    strcpy(this->obs, obs);
}

double Pedido::getTotal() const {
    return total;
}
void Pedido::setTotal(double total) {
    this->total = total;
}
