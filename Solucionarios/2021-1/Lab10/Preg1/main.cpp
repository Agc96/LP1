/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:07 AM
 */

#include "LFalta.h"

int main() {
    LFalta lf;
    lf.leer("RegistroDeFaltas1.csv");
    lf.imprimir("Reporte.txt");
    return 0;
}
