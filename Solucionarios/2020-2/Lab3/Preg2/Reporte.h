/*
 * Archivo: Reporte.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 10 de octubre de 2020, 05:42 PM
 */

#ifndef REPORTE_H
#define REPORTE_H

#include <iostream>
#include <fstream>
#include "StMedico.h"
using namespace std;

void leerMedicos(StMedico*, int&);

void leerPacientes(StMedico*, int);

void leerAcciones(StMedico*, int);
void modificarEstados(StMedico*, int, ifstream&);
void cancelarCitas(StMedico*, int, ifstream&);
void descartarPacientes(StMedico*, int, ifstream&);
void calcularIngresos(StMedico*, int, ifstream&);
void imprimirMedicos(StMedico*, int, ifstream&, ofstream&);

#endif /* REPORTE_H */
