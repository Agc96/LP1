/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 15 de mayo de 2021, 12:36 AM
 */

#include "funciones.h"

int main() {
    char **conductor, *gravedad;
    int *licencia, *infraccion;
    double *multa;
    cargarConductores(licencia, conductor);
    reporteConductores(licencia, conductor);
    cargarInfracciones(infraccion, gravedad, multa);
    reporteInfracciones(infraccion, gravedad, multa);
    reporteDeFaltas(licencia, conductor, infraccion, gravedad, multa);
    return 0;
}
