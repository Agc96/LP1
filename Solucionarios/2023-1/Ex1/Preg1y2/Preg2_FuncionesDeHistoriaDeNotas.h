/*
 * Archivo: Preg2_FuncionesDeHistoriaDeNotas.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de mayo de 2023, 09:50 PM
 */

#ifndef PREG2_FUNCIONESDEHISTORIADENOTAS_H
#define PREG2_FUNCIONESDEHISTORIADENOTAS_H

#include <iostream>
#include <fstream>
using namespace std;

enum IndiceNotaSemVeces{NOTA, SEMESTRE, VECES};

void cargarNotas(char ***&, int ***&, double **&, int **, char ***, double *,
        char ***, double *, const char *);
void inicializarEspaciosNotas(char ***&, int ***&, double **&, int **);
int buscarCurso(char ***, char *);
int buscarAlumno(int **, int);
double calcularMonto(int *, char **, double *, double);
void agregarCursoEnAlumno(char **, int **, double *, char *, int, int, double);
int buscarCursoLlevadoPorAlumno(char **, char *);
void asignarEspaciosExactosNotas(char ***, int ***, double **);
void copiarDatosNotas(char **, int **, double *, char **, int **, double *, int);
void pruebaDeCargaDeNotas(char ***, int ***, double **, int **, char ***,
        const char *);
void imprimirAlumnoParaReporteNotas(ofstream &, int *, char **);
void imprimirListaNotas(ofstream &, char **, int **, double *);
void imprimirResumenNotas(ofstream &, char **, double *);

#endif /* PREG2_FUNCIONESDEHISTORIADENOTAS_H */
