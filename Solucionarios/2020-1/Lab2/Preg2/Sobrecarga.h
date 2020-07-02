/* 
 * Archivo: Sobrecarga.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef SOBRECARGA_H
#define SOBRECARGA_H

#include <fstream>
#include "Alumno.h"
#include "ACurso.h"
using namespace std;

ifstream& operator >>(ifstream&, Alumno&);
ofstream& operator <<(ofstream&, Alumno&);
ifstream& operator >>(ifstream&, ACurso&);

/* Funciones auxiliares */
void separacion(ofstream&, char);

#endif /* SOBRECARGA_H */
