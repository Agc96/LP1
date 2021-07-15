/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Ambulatorio.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include "Ambulatorio.h"
using namespace std;

Ambulatorio::Ambulatorio() : Paciente() {
}

Ambulatorio::Ambulatorio(const Ambulatorio& orig) : Paciente(orig) {
}

Ambulatorio::~Ambulatorio() {
    // ~Paciente();
}

/* Métodos */

int Ambulatorio::orden() {
    return 1;
}

bool Ambulatorio::seguro() {
    return porcSeguro > 0;
}

istream& Ambulatorio::leer(istream& in) {
    double porcSeguro;
    Paciente::leer(in);
    // Leer el porcentaje del seguro
    in >> porcSeguro;
    in.get();
    setPorcSeguro(porcSeguro);
    return in;
}

ostream& Ambulatorio::imprimir(ostream& out) {
    Paciente::imprimir(out);
    out << right << setw(10) << getPorcSeguro() << endl;
    return out;
}

/* Encapsulamiento */

double Ambulatorio::getPorcSeguro() const {
    return porcSeguro;
}

void Ambulatorio::setPorcSeguro(double porcSeguro) {
    this->porcSeguro = porcSeguro;
}
