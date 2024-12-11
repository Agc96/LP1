/*
 * Archivo: Preg1_FuncionesDeCursosYAlumnos.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   19 de mayo de 2023, 08:58 PM
 */

#ifndef PREG1_FUNCIONESDECURSOSYALUMNOS_H
#define PREG1_FUNCIONESDECURSOSYALUMNOS_H

#include <iostream>
#include <fstream>
using namespace std;

enum IndicesCursos{COD_CURSO, NOM_CURSO, NOM_PROFE};
enum IndicesAlumnos{COD_ALUMNO, ESCALA, PORCENTAJE};
enum IndicesAlumnosNomMod{NOM_ALUMNO, MODALIDAD};

// Pregunta 1a
void cargarCursosYEscalas(char ***&, double *&, double *, const char *,
        const char *);
void cargarCursos(ifstream &, char ***&, double *&);
void incrementarEspaciosCursos(char ***&, double *&, int &, int &);
void cargarEscalas(ifstream &, double *);
void pruebaDeCargaDeCursos(char ***, double *, const char *);

// Pregunta 1b
void cargarAlumnos(int *&, int **&, char ***&, const char *);
void leerModalidadAlumno(ifstream &, char &, int &, int &);
void incrementarEspaciosAlumnos(int *&, int **&, char ***&, int &, int &);
void crearNodosAlumno(int, int, int, char *, char, int *&, char **&);
void pruebaDeCargaDeAlumnos(int *, int **, char ***, const char *);
void imprimirAlumno(ofstream &, int *, char **);

#endif /* PREG1_FUNCIONESDECURSOSYALUMNOS_H */
