/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 30 de septiembre de 2019, 05:30 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "cadena.h"
#define MAX_CURSOS 500
#define MAX_NUM 5
#define MAX_ESPECIALIDAD 30
#define MAX_CODIGO 10
#define MAX_CURSO 50
#define MAX_CREDITOS 10
#define MAX_LINEA 120

int leerArchivos(Cadena[], Cadena[], Cadena[], double[]);
void ordenarDatos(Cadena[], Cadena[], Cadena[], double[], int, int);
void cambiarDatos(Cadena[], Cadena[], Cadena[], double[], int, int);
void imprimirReporte(Cadena[], Cadena[], Cadena[], double[], int);
void imprimirResumen(ofstream&, Cadena&, Cadena&, double&);
void repetir(ofstream&, char, int = MAX_LINEA, bool = false);

#endif /* FUNCIONES_H */
