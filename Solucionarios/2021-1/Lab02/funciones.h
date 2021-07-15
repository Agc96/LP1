/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 23 de abril de 2021, 07:50 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void transferirConductores();
void guardarConductor(ofstream&, int, char*);
void guardarFalta(ofstream&, char*, int, int, char, int);

void transferirInfracciones();

void actualizarFaltas();
double buscarMontoInfraccion(ifstream&, int, int);
void actualizarConductores();
void calcularMontosConductor(ifstream&, int, int, int&, int&, int&, double&, double&, double&, double&);
void actualizarContadores(char, double, int&, int&, int&, double&, double&, double&, double&);

void actualizarFaltasAmnistia();
int solicitarFecha();
void aplicarDescuentoMonto(int, int, char, double&);

/* Reportes */

void imprimirReporte(const char*);
void imprimirReporteConductores(const char*);
void imprimirReporteInfracciones(const char*);
void imprimirConductores(ofstream&);
void imprimirFaltas(ofstream&);
void imprimirInfracciones(ofstream&);

/* Funciones auxiliares */

ifstream abrirArchTexto(const char*);
ofstream crearArchTexto(const char*);
ifstream abrirArchBin(const char*);
ofstream crearArchBin(const char*);
fstream actualizarArchBin(const char*);
int calcularNumRegistros(istream&, int);
int convertirFecha(int, int, int);
void imprimirFecha(ofstream&, int);

#endif /* FUNCIONES_H */
