/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 8 de mayo de 2020, 09:29 AM
 */

#include "funciones.h"

int main() {
    // Parte 1: Crear el archivo binario de alumnos
    transferirArchivoAlumnos("Alumnos.bin", "Alumnos.txt");
    // Parte 2: Crear el archivo consolidado
    crearArchivoConsolidado("Consolidado.bin", "Alumnos.bin");
    actualizarArchivoConsolidado("Consolidado.bin", "Cursos.txt");
    // Parte 3: Generar reporte consolidado
    generarReporteConsolidado("Reporte.txt", "Alumnos.bin", "Consolidado.bin");
    return 0;
}
