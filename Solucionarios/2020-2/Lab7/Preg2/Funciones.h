/*
 * Archivo: Funciones.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include "Paciente.h"
#include "Medico.h"
using namespace std;

void leerMedicos(Medico*, int&);

void leerPacientes(Medico*, int);
int buscarMedico(Medico*, int, char*);

void leerAcciones(Medico*, int);
void modificarEstados(Medico*, int, ifstream&);
void cancelarCitas(Medico*, int, ifstream&);
void calcularIngresos(Medico*, int, ifstream&);
void imprimirMedico(Medico*, int, ifstream&, ofstream&);

// Funciones auxiliares
ifstream abrirArchivo(const char*);
ofstream crearArchivo(const char*);

#endif /* FUNCIONES_H */
