/* 
 * Archivo: alumno.h
 * Autor:   Anthony Gutiérrez
 *
 * Creado el 15 de mayo de 2020, 08:19 AM
 */

#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_CADENA 50
#define MAX_ARREGLO 100
#define MAX_LINEA 80

struct Alumno {
    int codigo;
    char tipo;
    char nombre[MAX_CADENA];
    int curso[MAX_ARREGLO];
    int ciclo[MAX_ARREGLO];
    int nota[MAX_ARREGLO];
    double credito[MAX_ARREGLO];
    int numcur = 0;
};

struct ACurso {
    int codigo;
    int curso;
    int ciclo;
    int nota;
    double credito;
    char operacion;
};

void operator +(const Alumno&, const ACurso&);
void operator *(const Alumno&, const ACurso&);
void operator -(const Alumno&, const ACurso&);
double operator /(const Alumno&, int);
double operator --(const Alumno&);
double operator ++(const Alumno&);
istream& operator >>(istream&, const Alumno&);
istream& operator >>(istream&, const ACurso&);
ostream& operator <<(ostream&, const Alumno&);

void separador(ostream&);

#endif /* ALUMNO_H */
