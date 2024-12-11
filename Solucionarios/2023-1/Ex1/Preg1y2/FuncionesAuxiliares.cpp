/*
 * Archivo: FuncionesAuxiliares.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   20 de mayo de 2023, 10:09 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "FuncionesAuxiliares.h"
using namespace std;

#define MAX_BUFFER 100

char *leerCadenaDinamicaYExacta(ifstream &arch, char delim) {
    char buffer[MAX_BUFFER], *cadena;
    arch.getline(buffer, MAX_BUFFER, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void imprimirLinea(ofstream &archRep, char car, int num) {
    for (int i = 0; i < num; i++)
        archRep.put(car);
    archRep << endl;
}
