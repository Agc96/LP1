/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 26 de noviembre de 2020, 07:50 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

void leerTarifas(int *&, double *&);

void leerPacientes(void *&, int *, double *);
void leerDatos(istream &, int &, char *, char &, int &, double &, double &);
void *crearPaciente(int, char *, int, double, double, int *, double *, char);
double buscarTarifa(int *, double *, int);
int compararPacientes(void *, void *);
int convertirTipoPaciente(void *);

void atenderPacientes(void *);
void imprimirPaciente(ostream &, void *, int, double &);
void imprimirTipoPaciente(ostream &, char);
void eliminarPrioridad(void *);

void limpiarEspacios(void *, int *, double *);

/* Funciones auxiliares */

char *crearPunteroChar(char);
int *crearPunteroInt(int);
double *crearPunteroDouble(double);
char *crearPunteroCadena(char *);
void separacion(ostream &, char);

#endif /* FUNCIONES_H */
