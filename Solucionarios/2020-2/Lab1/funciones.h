/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 18 de septiembre de 2020, 08:14 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void procesarAlumnos();
void procesarAlumno(int);
void imprimirCabeceraAlumno(int, int, char*);
void procesarCursoAlumno(int, int, int&, double&, double&, int&, int&, double&, double&);
void imprimirCursoAlumno(int, char*, double, int, int, int, int);
void imprimirResumenAlumno(int, double, double, int, int, double, double);

// Funciones auxiliares
void separacion(char);

#endif /* FUNCIONES_H */
