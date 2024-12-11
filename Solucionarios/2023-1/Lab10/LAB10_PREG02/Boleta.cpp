/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:24 AM
 */

#include <iostream>
#include <fstream>
#include "Boleta.h"
#include "Presencial.h"
#include "Semipresencial.h"
#include "Virtual.h"
using namespace std;

Boleta::Boleta() {
    pboleta = nullptr;
}

Boleta::Boleta(const Boleta& orig) {
}

Boleta::~Boleta() {
    if (pboleta) delete pboleta;
}

/* Métodos */

void Boleta::leer(ifstream &arch, char tipo) {
    switch (tipo) {
        case 'P':
            pboleta = new Presencial;
            break;
        case 'S':
            pboleta = new Semipresencial;
            break;
        case 'V':
            pboleta = new Virtual;
            break;
    }
    pboleta->lee(arch);
}

int Boleta::getCodigo() {
    return pboleta ? pboleta->GetCodigo() : NO_ENCONTRADO;
}

int Boleta::getEscala() {
    return pboleta ? pboleta->GetEscala() : NO_ENCONTRADO;
}

void Boleta::actualizar(double precio) {
    if (pboleta) pboleta->actualizatotal(precio);
}

void Boleta::imprimir(ofstream &arch) {
    if (pboleta) pboleta->imprime(arch);
    else arch << "Boleta vacia" << endl;
}
