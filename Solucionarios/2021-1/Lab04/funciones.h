/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 15 de mayo de 2021, 12:38 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

/* Pregunta 1 */
void cargarConductores(int*&, char**&);
void crearArrConductoresExactos(int*&, char**&, int*, char**, int);
void reporteConductores(int*, char**);

/* Pregunta 2 */
void cargarInfracciones(int*&, char*&, double*&);
void crearArrInfraccionesExactos(int*&, char*&, double*&, int*, char*,
        double*, int);
void reporteInfracciones(int*, char*, double*);

/* Pregunta 3 */
void reporteDeFaltas(int*, char**, int*, char*, double*);
void cargarFaltasPorGravedad(int*, char*, double*, int*&, char**&, int*&,
        double*&, char);
void agregarFalta(int*, char**, int*, double*, int, char*, double, int&);
void crearArrFaltasExactos(int*&, char**&, int*&, double*&, int*, char**,
        int*, double*, int);
char obtenerTipoGravedad(int);
int buscarInfraccion(int*, int);
int buscarLicFalta(int*, char**, int, char*, int);
void reporteFaltasPorGravedad(ofstream&, int*, char**, int*, double*, int);
void imprimirCabeceraFaltas(ofstream&, int);
void liberarEspaciosFaltas(int*, char**, int*, double*);
void liberarEspaciosCondInf(int*, char**, int*, char*, double*);

/* Funciones auxiliares */
ifstream abrirArchivo(const char*);
ofstream crearArchivo(const char*);
char* crearCadenaExacta(char*);
void imprimirLinea(ofstream&, char, int);

#endif /* FUNCIONES_H */
