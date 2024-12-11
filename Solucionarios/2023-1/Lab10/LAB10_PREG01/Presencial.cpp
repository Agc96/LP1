/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:20 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Presencial.h"
using namespace std;

Presencial::Presencial() {
    total = 0;
}

Presencial::Presencial(const Presencial& orig) {
}

Presencial::~Presencial() {
    // No es necesario hacer nada aquí
}

/* Encapsulamiento */

double Presencial::GetRecargo() const {
    return recargo;
}

void Presencial::SetRecargo(double recargo) {
    this->recargo = recargo;
}

double Presencial::GetTotal() const {
    return total;
}

void Presencial::SetTotal(double total) {
    this->total = total;
}

/* Métodos */

void Presencial::lee(ifstream &arch) {
    Alumno::lee(arch);
    arch >> recargo;
}

void Presencial::imprime(ofstream &arch) {
    Alumno::imprime(arch);
    arch << setw(12) << GetRecargo() << setw(13) << GetTotal()
            << setw(10) << Alumno::GetTotal() << endl;
}
