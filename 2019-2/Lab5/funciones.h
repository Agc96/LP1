/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 4 de octubre de 2019, 11:11 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

#define MAX_ALMACEN 100
#define MAX_NUMERO 4
#define TAM_CODIGO 8
#define MAX_CODIGO 12
#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 70
#define MAX_CABECERA 25
#define MAX_LINEA 120

void leerPalets(char***&);
char* leerCodigoProducto(istream&, char);
void incrementarAlmacen(char***, char*, int, int&);

void imprimirPalets(char***);
void separacion(ostream&, char = '=');

void leerProductos(char**&, char**&);
char* leerNombreProducto(istream&);

void imprimirProductos(char**, char**);

void ordenarProductos(char**, char**);
void ordenarProductos(char**, char**, int, int);
void cambiarProductos(char**, char**, int, int);

void cuentaProductos(char***, char**, char**);
int obtenerNumeroPalets(char***, char*);

#endif /* FUNCIONES_H */
