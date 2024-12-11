/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 05:08 PM
 */

#include "funciones.h"

int main() {
    inicializarArchivos();
    procesarAlumnosxCursos();
    procesarEscalas();
    imprimirReporteVerificacion("ReporteVerifAntes.txt");
    actualizarAlumnosCursos();
    imprimirReporteVerificacion("ReporteVerifDespues.txt");
    imprimirReporteFinal();
    return 0;
}

