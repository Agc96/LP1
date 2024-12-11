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

int Boleta::comparar(const Boleta &otro) {
    return pboleta->GetCodigo() - otro.pboleta->GetCodigo();
}

void Boleta::imprimir(ofstream &arch) {
    pboleta->imprime(arch);
}
