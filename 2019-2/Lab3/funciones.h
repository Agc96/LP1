/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 20 de septiembre de 2019, 10:44 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void generarRegistroBinario(ifstream&);
void obtenerDetallesVenta(ifstream&, int&, char&, int&, double&, int&);

void actualizarMontos(ifstream&, ifstream&);
double buscarPrecioProducto(ifstream&, int, int, int);
void actualizarRegistroVentas(fstream&, int, double);

void generarReporte(ofstream&);
void escribirCabeceraReporte(ofstream&);
void escribirDetallesVenta(ofstream&, int, int, char, int, double, int, double&);
void escribirResumenReporte(ofstream&, double);

#endif /* FUNCIONES_H */
