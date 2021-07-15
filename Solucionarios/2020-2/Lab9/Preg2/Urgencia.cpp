/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: Urgencia.cpp
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <iomanip>
#include "Urgencia.h"
using namespace std;

Urgencia::Urgencia() : Paciente() {
}

Urgencia::Urgencia(const Urgencia& orig) : Paciente(orig) {
}

Urgencia::~Urgencia() {
}

/* Métodos */

int Urgencia::orden() {
    return 2;
}

bool Urgencia::seguro() {
    return porcSeguro > 0;
}

istream& Urgencia::leer(istream& in) {
    double porcSeguro, porcUrgencia;
    Paciente::leer(in);
    // Leer el porcentaje del seguro
    in >> porcSeguro;
    in.get();
    setPorcSeguro(porcSeguro);
    // Leer el porcentaje de urgencia
    in >> porcUrgencia;
    in.get();
    setPorcUrgencia(porcUrgencia);
    return in;
}

ostream& Urgencia::imprimir(ostream& out) {
    Paciente::imprimir(out);
    out << right << setw(10) << getPorcSeguro() << setw(4) << ' ';
    out << right << setw(10) << getPorcUrgencia() << endl;
    return out;
}

/* Encapsulamiento */

double Urgencia::getPorcSeguro() const {
    return porcSeguro;
}

void Urgencia::setPorcSeguro(double porcSeguro) {
    this->porcSeguro = porcSeguro;
}

double Urgencia::getPorcUrgencia() const {
    return porcUrgencia;
}

void Urgencia::setPorcUrgencia(double porcUrgencia) {
    this->porcUrgencia = porcUrgencia;
}
