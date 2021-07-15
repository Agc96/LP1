/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 9 de octubre de 2020, 08:47 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

void cargarMedicos(char**&, char**&, double*&);
void reporteMedicos(char**, char**, double*);
void reporteDeIngresos(char**, char**, double*);
void cargarPacientes(char*, int*&, char**&, double*&, int*&);
void agregarPaciente(int, char*, double, int&, int*, char**, double*, int*);
void reporteDelMedico(char*, char**, char**, double*, int*, char**, double*, int*, ofstream&);
void imprimirPacientes(int*, char**, double*, int*, double, double&, double&, int&, ofstream&);
void liberarEspacios(int*, char**, double*, int*);

/* Funciones auxiliares */
ifstream abrirArchivoEntrada(const char*);
ofstream abrirArchivoSalida(const char*);
char* crearCadenaExacta(char*);
char** crearArrCadenas(char**, int);
double* crearArrDouble(double*, int);
int* crearArrEnteros(int*, int);
void liberarArrCadenas(char**);
void imprimirLinea(ofstream&, char, int);

#endif /* FUNCIONES_H */
