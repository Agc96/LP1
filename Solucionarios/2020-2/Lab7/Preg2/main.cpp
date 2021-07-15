/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 */

#include "Medico.h"
#include "Funciones.h"

#define MAX_MEDICOS 50

int main() {
    Medico medicos[MAX_MEDICOS];
    int numMedicos;
    leerMedicos(medicos, numMedicos);
    leerPacientes(medicos, numMedicos);
    leerAcciones(medicos, numMedicos);
    return 0;
}
