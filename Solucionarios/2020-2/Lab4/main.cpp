/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 9 de octubre de 2020, 08:45 AM
 */

#include "Laboratorio04_Funciones.h"

int main() {
    char **codigoMed, **medicos;
    double *tarifas;
    cargarMedicos(codigoMed, medicos, tarifas);
    reporteMedicos(codigoMed, medicos, tarifas);
    reporteDeIngresos(codigoMed, medicos, tarifas);
    return 0;
}
