/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de septiembre de 2022, 01:07 AM
 */

#include "funciones.h"

int main(int argc, char** argv) {
    char **med_Nombre, **med_Especialidad, **pac_Nombre;
    int *med_Codigo, *pac_Dni, **pac_Citas;
    double *med_Tarifa;
    lecturaDeMedicos("Medicos.csv", med_Codigo, med_Nombre, med_Especialidad,
            med_Tarifa);
    pruebaDeLecturaDeMedicos("ReporteDeMedicos.txt", med_Codigo, med_Nombre,
            med_Especialidad, med_Tarifa);
    lecturaDeCitas("Citas.csv", pac_Dni, pac_Nombre, pac_Citas);
    pruebaDeLecturaDeCitas("ReporteDeCitas.txt", pac_Dni, pac_Nombre, pac_Citas);
    reporteDeIngresosMedicosYGastosDeLosPacientes("ReporteDeIngresosMedicos.txt",
            med_Codigo, med_Nombre, med_Especialidad, med_Tarifa, pac_Dni,
            pac_Nombre, pac_Citas);
    return 0;
}
