/*
 * Archivo: BibMedicos.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 2 de octubre de 2020, 08:54 AM
 */

#ifndef BIBMEDICOS_H
#define BIBMEDICOS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "StMedico.h"
#include "StPaciente.h"
using namespace std;

/* Lectura */
istream& operator >>(istream&, StMedico&);
istream& operator >>(istream&, StPaciente&);

/* Agregación */
void operator +(StMedico&, StPaciente&);

/* Modificación de estado */
void operator +(StMedico&, int);

/* Cancelación de citas */
void operator -(StMedico&, int);

/* Descarte */
void operator /(StMedico&, int);

/* Cálculo de ingresos */
void operator ++(StMedico&);

/* Impresión */
ostream& operator <<(ostream&, StMedico&);
void imprimirPacientes(ostream&, StMedico&, char);

/* Funciones auxiliares */
void imprimirLinea(ostream&, char);
void imprimirContador(ostream&, int);
void imprimirFecha(ostream&, int);

#endif /* BIBMEDICOS_H */
