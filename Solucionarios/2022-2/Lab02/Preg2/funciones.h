/*
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   11 de septiembre de 2022, 11:45 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void inicializarArchBin();

void completaBinarioPacientes();
double buscarPrecioMedicina(int);
void actualizarPaciente(int, double);

void reporteFinal();
void reporteMedicos(fstream &);
void reportePacientes(fstream &);
void reporteMedicinas(fstream &);
void reporteConsultas(fstream &);
void obtenerEspecialidad(char *, char *);

// Funciones auxiliares
fstream abrirArchivo(const char *, ios::openmode);
int obtenerNumReg(fstream &, int);
void formatearNombre(char *);
void imprimirFecha(fstream &, int);
void imprimirLinea(fstream &, char);

#endif /* FUNCIONES_H */
