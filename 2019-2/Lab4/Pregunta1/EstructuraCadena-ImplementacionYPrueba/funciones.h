/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 27 de septiembre de 2019, 03:34 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
#include "cadena.h"
using namespace std;

void pruebaInicializacionLongitud(ofstream&);
void pruebaRecortarCadenas(ofstream&, ifstream&);
void pruebaIntercambiarCadenas(ofstream&, ifstream&);
void pruebaSobrecarga(ofstream&, ifstream&);

void imprimirDetalle(ofstream&, Cadena&);
void separacion(ofstream&, char);

#endif /* FUNCIONES_H */
