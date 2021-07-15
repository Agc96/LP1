/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 11 de diciembre de 2020, 09:32 AM
 */

#include "ListaPacientes.h"

int main() {
    ListaPacientes l;
    l.creaLista("AtencionDeCitas.csv");
    l.imprimeLista("Reporte.txt");
    return 0;
}
