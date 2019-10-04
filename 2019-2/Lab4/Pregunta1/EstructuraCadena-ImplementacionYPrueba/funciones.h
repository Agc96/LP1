/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 03:34 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "cadena.h" // TODO: Cambiar nombre por el header del alumno
using namespace std;

void jpPruebaCadenas();
void jpImprimirCadena(ofstream&, Cadena&, const char*);
void jpImprimirComparacion(ofstream&, bool, const char*);

#endif /* FUNCIONES_H */
