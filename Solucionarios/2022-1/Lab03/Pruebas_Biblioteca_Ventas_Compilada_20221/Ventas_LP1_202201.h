/*
 * Archivo: Ventas_LP1_202201.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   2 de mayo de 2022, 12:10 PM
 */

#ifndef VENTAS_LP1_202201_H
#define VENTAS_LP1_202201_H

#include <iostream>
#include <fstream>
#include "Estructuras.h"
using namespace std;

// Sobrecargas de lectura
ifstream& operator >>(ifstream&, Estructura_ClienteRegistrado&);
// Sobrecargas de agregación
void operator +=(Estructura_ClienteRegistrado[], Estructura_ClienteRegistrado&);
void operator +=(Estructura_ClienteRegistrado&, Estructura_PedidoRealizado&);
void operator +=(Estructura_ProductosEnAlmacen[], Estructura_ProductosEnAlmacen&);
// Sobrecargas de impresión
ofstream& operator <<(ofstream&, Estructura_ClienteRegistrado&);
ofstream& operator <<(ofstream&, Estructura_ProductosEnAlmacen[]);

#endif /* VENTAS_LP1_202201_H */

