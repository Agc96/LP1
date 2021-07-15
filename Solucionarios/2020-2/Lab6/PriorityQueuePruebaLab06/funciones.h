/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 12:10 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

void leerNumeros(void *&);
int *crearPunteroInt(int);
int ordenarEnteros(void *, void *);

void imprimirReporte(void *);
void imprimirEnteros(ostream &, void *, void *);
void separacion(ostream &, char);

#endif /* FUNCIONES_H */
