/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 11 de octubre de 2019, 10:36 AM
 */

#include <fstream>
using namespace std;

#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_BUFFER 500
#define MAX_LINEA 120
#define MAX_CODIGO 25
#define MAX_NOMBRE 60
#define MAX_NUM 25

void leerPalets(void*&);
void* generarPalet(ifstream&);
void* generarArregloExacto(void*[], int);

void imprimirPalets(void*);
void imprimirPalet(ofstream&, void**);
void separacion(ofstream&, char = '=', int = MAX_LINEA);

void leerProductos(void*&);
void* generarProducto(ifstream&);

void imprimirProductos(void*);
void imprimirProducto(ofstream&, void**);

void ordenarProductos(void*);
void ordenarProductos(void***, int, int);
void cambiarProductos(void***, int, int);

void cargaStock(void*, void*);
int calcularStock(void***, char*);

#endif /* FUNCIONES_H */
