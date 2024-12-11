/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de septiembre de 2022, 06:15 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void separarMedicosConsultas();
void inicializarArchBin();
void leerMedicosConsultas(fstream&);
void agregarMedico(fstream &, char *, char *);
void agregarPaciente(fstream &, int, char *, double);
void agregarMedicina(fstream &, int, char *, double);
void reporteMedicos(fstream &);
void reportePacientes(fstream &);
void reporteMedicinas(fstream &);
void reporteConsultas(fstream &);

// Funciones auxiliares
fstream abrirArchivo(const char *, ios::openmode);
int obtenerNumReg(fstream &, int);
void imprimirLinea(fstream &, char);

#endif /* FUNCIONES_H */
