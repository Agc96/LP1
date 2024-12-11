/*
 * Archivo: Funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 10:08 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include "Alumno.h"
#include "AlumnoNota.h"
using namespace std;

void cargaralumnos(Alumno *);
void carganotas(AlumnoNota *);

void actualizanotas(Alumno *, AlumnoNota *);
int buscarAlumno(Alumno *, int);
bool cursoYaProcesado(AlumnoNota *, int);
bool esMismoAlumnoYCurso(AlumnoNota &, AlumnoNota &);
void obtenerUltimaNota(AlumnoNota *, int , int &, int &);
void agregarNota(Alumno &, AlumnoNota &, int);

void actualizanotas2(Alumno *, AlumnoNota *);
void ordenarNotas(AlumnoNota *);
bool verificarOrdenNotas(AlumnoNota &, AlumnoNota &);
void intercambiarObjeto(AlumnoNota &, AlumnoNota &);
void pruebaOrdenamiento(AlumnoNota *);
int obtenerNumVeces(AlumnoNota *, int);

void imprimealumnos(Alumno *);

void abrirArchivoEntrada(ifstream &, const char *);
void abrirArchivoSalida(ofstream &, const char *);

#endif /* FUNCIONES_H */
