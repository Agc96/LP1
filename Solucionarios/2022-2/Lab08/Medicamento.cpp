/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Medicamento.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de noviembre de 2022, 02:44 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Medicamento.h"
using namespace std;

Medicamento::Medicamento() {
    codigo = 0;
    nombre = nullptr;
}

Medicamento::Medicamento(const Medicamento& orig) {
}

Medicamento::~Medicamento() {
    if (nombre) delete nombre;
}

/* Métodos */

void Medicamento::asignar(int codigo, int cantidad, int fecha) {
    SetCodigo(codigo);
    SetCantidad(cantidad);
    SetFecha(fecha);
}

void Medicamento::leer() {
    ifstream arch("medicamentos.csv", ios::in);
    if (!arch) {
        cerr << "No se encontro el archivo de medicamentos" << endl;
        exit(1);
    }
    char nombre[50];
    int codigo;
    double precio;
    // Leer línea por línea
    while (true) {
        arch >> codigo;
        if (arch.eof()) break;
        if (codigo == GetCodigo()) {
            arch.get();
            arch.getline(nombre, 50, ',');
            SetNombre(nombre);
            arch >> precio;
            SetPrecio(precio);
            break;
        } else {
            while (arch.get() != '\n');
        }
    }
}

void Medicamento::imprimir(ofstream &arch) {
    char nombre[50];
    GetNombre(nombre);
    arch << left << setw(10) << GetCodigo() << setw(40) << nombre
            << right << setw(5) << GetCantidad();
}

/* Encapsulamiento */

int Medicamento::GetCodigo() const {
    return codigo;
}

void Medicamento::SetCodigo(int codigo) {
    this->codigo = codigo;
}

void Medicamento::GetNombre(char *nombre) const {
    if (this->nombre) strcpy(nombre, this->nombre);
    else nombre[0] = 0;
}

void Medicamento::SetNombre(const char *nombre) {
    if (this->nombre) delete this->nombre;
    this->nombre = new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);
}

int Medicamento::GetCantidad() const {
    return cantidad;
}

void Medicamento::SetCantidad(int cantidad) {
    this->cantidad = cantidad;
}

double Medicamento::GetPrecio() const {
    return precio;
}

void Medicamento::SetPrecio(double precio) {
    this->precio = precio;
}

int Medicamento::GetFecha() const {
    return fecha;
}

void Medicamento::SetFecha(int fecha) {
    this->fecha = fecha;
}
