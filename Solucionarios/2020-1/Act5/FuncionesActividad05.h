/* 
 * Archivo: FuncionesActividad05.h
 * Autor:   Anthony Gutiérrez
 */

#include <iostream>
#include <fstream>
using namespace std;

#ifndef FUNCIONESACTIVIDAD05_H
#define FUNCIONESACTIVIDAD05_H

void leerAlumnos(void*&);
void* crearRegistro(ifstream&);

void imprimirAlumnos(void*);

void leerCursos(void*);
void actualizarAlumnos(void*, int, char*, int, double);
void actualizarAlumno(void**, char*, int, double);
void* agregarConIncremento(void**, void*);

void consolidado(void*);
void imprimirAlumno(ofstream&, void**);
void imprimirCursos(ofstream&, void*);

void validarArchivo(ios&, const char*);
int* crearEntero(int);
double* crearReal(double);
char* crearCadena(char*);
void separacion(ostream&);

#endif /* FUNCIONESACTIVIDAD05_H */
