/*
 * Archivo: main.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de mayo de 2023, 08:54 PM
 */

#include "Preg1_FuncionesDeCursosYAlumnos.h"
#include "Preg2_FuncionesDeHistoriaDeNotas.h"

int main() {
    char ***cursos, ***alumnos_nom_mod;
    double *cursos_cred, escalas[5];
    int *alumnos_cod, **alumnos;
    cargarCursosYEscalas(cursos, cursos_cred, escalas, "Cursos.csv", "Escalas.csv");
    pruebaDeCargaDeCursos(cursos, cursos_cred, "PruebaCursos.txt");
    cargarAlumnos(alumnos_cod, alumnos, alumnos_nom_mod, "Alumnos.csv");
    pruebaDeCargaDeAlumnos(alumnos_cod, alumnos, alumnos_nom_mod, "PruebaAlumnos.txt");
    char ***cursos_cod;
    int ***cursos_nota_sem_veces;
    double **costos;
    cargarNotas(cursos_cod, cursos_nota_sem_veces, costos, alumnos, alumnos_nom_mod,
            escalas, cursos, cursos_cred, "HistoriaDeNotas.csv");
    pruebaDeCargaDeNotas(cursos_cod, cursos_nota_sem_veces, costos, alumnos,
            alumnos_nom_mod, "PruebaDeNotas.txt");
    return 0;
}
