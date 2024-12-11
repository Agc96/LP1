/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   23 de abril de 2023, 05:08 PM
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
void imprimirReporteVerificacion(const char *);
void imprimirCursos(ofstream &);
void imprimirAlumnos(ofstream &);
void imprimirClases(ofstream &);
void imprimirEscalas(ofstream &);
void actualizarAlumnosCursos();
int buscarCurso(fstream &, int, const char *);
void procesarClase(fstream &, fstream &, ifstream &, int, int, int, int);
void imprimirReporteFinal();
void imprimirAlumnosEnCurso(ofstream &, const char *);

// Funciones auxiliares
ifstream abrirArchEntrada(const char *, bool);
ofstream abrirArchSalida(const char *, bool);
fstream abrirArchBinEntSal(const char *);
int obtenerNumReg(istream &, int);
void imprimirLinea(ofstream &, char, int);
void formatearNombre(char *);

#endif /* FUNCIONES_H */

