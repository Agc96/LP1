/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 12:22 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void inicializarArchivos();
void procesarAlumnosxCursos();
void agregarCurso(ofstream &, char *, char *, double, int, char *, int &);
void procesarAlumno(fstream &, int, int, char *, char, int, int, double);
int buscarAlumno(fstream &, int, int, int);
void agregarClase(ofstream &, char *, int, int);
void procesarEscalas();
void imprimirReporteVerificacion();
void imprimirCursos(ofstream &);
void imprimirAlumnos(ofstream &);
void imprimirClases(ofstream &);
void imprimirEscalas(ofstream &);

// Funciones auxiliares
ifstream abrirArchEntrada(const char *, bool);
ofstream abrirArchSalida(const char *, bool);
fstream abrirArchBinEntSal(const char *);
int obtenerNumReg(fstream &, int);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */
