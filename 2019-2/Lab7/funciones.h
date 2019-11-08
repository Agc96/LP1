/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 8 de noviembre de 2019, 10:15 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX_LINEA 120
#define MAX_PRODUCTO 10
#define MAX_PALET 10
#define MAX_CANTIDAD 10

// Funciones para listas genéricas
void crealista(void*&, void*(*)(ifstream&), int(*)(const void*, const void*));
void** crearNodo(void* registro);
void insertarNodoOrdenado(void*&, void**, int(*)(const void*, const void*));
void imprimelista(void*, void(*)(ofstream&, void*));

// Funciones para colas genéricas
void encola(void*&, void*);
void* desencola(void*&);

// Funciones para registros de palets
void* leerRegistro(ifstream&);
void* crearRegistro(char*, char*, int);
int comparar(const void*, const void*);
void imprimeRegistro(ofstream&, void*);

// Funciones para registro de despachos
void despacha(void*&, void*&, int, char**);
void despacharProducto(void*&, void*&, char*, int&);
void actualizarPalet(void*&, void*&, void**&, void**&, void**, int&);
void imprimedespachados(void*, void(*)(ofstream&, void*));

#endif /* FUNCIONES_H */
