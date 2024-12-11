/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 12:22 AM
 */

#include "funciones.h"

int main() {
    inicializarArchivos();
    procesarAlumnosxCursos();
    procesarEscalas();
    imprimirReporteVerificacion();
    return 0;
}
