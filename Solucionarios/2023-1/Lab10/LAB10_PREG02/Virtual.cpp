/*
 * Archivo: Alumno.cpp
 * Autor:   Anthony Gutiérrez
 * 
 * Creado el 30 de junio de 2023, 08:21 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Virtual.h"
using namespace std;

Virtual::Virtual() {
    licencia = nullptr;
    total = 0;
}

Virtual::Virtual(const Virtual& orig) {
}

Virtual::~Virtual() {
    if (licencia) delete[] licencia;
}

/* Encapsulamiento */

void Virtual::GetLicencia(char *cad) const {
    if (licencia) strcpy(cad, licencia);
    else cad[0] = 0;
}

void Virtual::SetLicencia(const char *cad) {
    if (licencia) delete[] licencia;
    licencia = new char[strlen(cad)+1];
    strcpy(licencia, cad);
}

double Virtual::GetTotal() const {
    return total;
}

void Virtual::SetTotal(double total) {
    this->total = total;
}

/* Métodos */

void Virtual::lee(ifstream &arch) {
    char licencia[MAX_LIC_VIRTUAL];
    Alumno::lee(arch);
    arch.getline(licencia, MAX_LIC_VIRTUAL);
    SetLicencia(licencia);
}

void Virtual::actualizatotal(double precio) {
    double monto = GetCreditos() * precio;
    SetTotal(MONTO_VIRTUAL);
    Alumno::SetTotal(monto + GetTotal());
}

void Virtual::imprime(ofstream &arch) {
    char licencia[MAX_LIC_VIRTUAL];
    Alumno::imprime(arch);
    GetLicencia(licencia);
    arch << setw(2) << ' ' << left << setw(MAX_LIC_VIRTUAL) << licencia
            << right << setw(10) << Alumno::GetTotal() << endl;
}
