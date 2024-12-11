/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   28 de septiembre de 2022, 01:17 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

// Pregunta 1
void lecturaDeMedicos(const char *, int *&, char **&, char **&, double *&);
void procesarNombre(char *, char *&, char *&);
void pruebaDeLecturaDeMedicos(const char *, int *, char **, char **, double *);

// Pregunta 2
void lecturaDeCitas(const char *, int *&, char **&, int **&);
void agregarCita(int *, int, int);
int *copiarCitas(int *);
void pruebaDeLecturaDeCitas(const char *, int *, char **, int **);

// Pregunta 3
void reporteDeIngresosMedicosYGastosDeLosPacientes(const char *, int *, char **,
        char **, double *, int *, char **, int **);
void reporteFinalDeMedicos(ofstream &, int *, char **, char **, double *, int **);
double calcularIngresosMedico(int, double, int **);
void reporteFinalDePacientes(ofstream &, int *, char **, int **, int *, double *);
double obtenerGastosPaciente(int *, int *, double *);

// Funciones auxiliares
char *crearCadenaExacta(char *);
int buscarEnArreglo(int *, int);
int obtenerCantDatos(int *);
void imprimirFecha(ofstream &, int);
void imprimirLinea(ofstream &, char, int);

#endif /* FUNCIONES_H */
