/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 10 de octubre de 2020, 05:39 PM
 */

#include "Reporte.h"
#define MAX_MEDICOS 50

int main(int argc, char** argv) {
    StMedico medicos[MAX_MEDICOS];
    int numMedicos = 0;
    // Leer los datos de los médicos
    leerMedicos(medicos, numMedicos);
    // Leer los datos de los pacientes
    leerPacientes(medicos, numMedicos);
    // Leer las acciones a realizar
    leerAcciones(medicos, numMedicos);
    return 0;
}
