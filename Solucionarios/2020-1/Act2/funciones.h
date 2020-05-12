/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 8 de mayo de 2020, 04:37 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Parte 1: Crear el archivo binario de alumnos
void transferirArchivoAlumnos(const char*, const char*);
// Parte 2: Crear el archivo consolidado
void crearArchivoConsolidado(const char*, const char*);
void actualizarArchivoConsolidado(const char*, const char*);
void actualizarAlumnoConsolidado(fstream&, int, double, int);
// Parte 3: Generar reporte consolidado
void generarReporteConsolidado(const char*, const char*, const char*);
void imprimirCabeceraReporte(ofstream&);
void imprimirAlumnoReporte(ofstream&, int, char*, int, double, double, double, int);
void imprimirResumenReporte(ofstream&, int, int, int, int);
// Funciones auxiliares
void validarArchivo(ios&, const char*);
int obtenerCantArchBin(istream&, int);
void separador(ostream&);
void espacios(ostream&, int);
void repetir(ostream&, char, int, bool);

#endif /* FUNCIONES_H */
