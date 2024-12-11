/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   21 de mayo de 2023, 06:52 PM
 */

#include "Preg1_FuncionesDeCursosYAlumnos.h"
#include "Preg3_PunterosGenericos.h"
#include "FuncionesAuxiliares.h"

int main() {
    int *alumnos_cod, **alumnos;
    void *alumnoveces;
    char ***alumnos_nom_mod;
    cargarAlumnos(alumnos_cod, alumnos, alumnos_nom_mod, "Alumnos.csv");
    CargaCursos(alumnos_cod, alumnoveces, "HistoriaDeNotas.csv");
    ActualizaVeces(alumnoveces);
    ImprimeAlumno(alumnoveces);
    return 0;
}
