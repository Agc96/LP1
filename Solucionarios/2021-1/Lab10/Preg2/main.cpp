/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 16 de julio de 2021, 12:07 AM
 */

#include "LFalta.h"

int main() {
    LFalta lf1, lf2;
    lf1.leer("RegistroDeFaltas1.csv");
    lf2.leer("RegistroDeFaltas2.csv");
    lf1.unir(lf2);
    lf1.imprimir("Reporte.txt");
    return 0;
}
