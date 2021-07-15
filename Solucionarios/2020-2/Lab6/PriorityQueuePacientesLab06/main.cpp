/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 07:49 PM
 */

#include "funciones.h"

int main() {
    void *cola;
    int *arrCodEspec;
    double *arrTarifas;
    leerTarifas(arrCodEspec, arrTarifas);
    leerPacientes(cola, arrCodEspec, arrTarifas);
    atenderPacientes(cola);
    limpiarEspacios(cola, arrCodEspec, arrTarifas);
    return 0;
}
