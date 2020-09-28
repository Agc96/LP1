/* 
 * Archivo: Sobrecarga.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef SOBRECARGA_H
#define SOBRECARGA_H

#include <iostream>
#include "Persona.h"
#include "Alumno.h"
#include "Profesor.h"
using namespace std;

istream& operator >>(istream&, class Persona&);
ostream& operator <<(ostream&, class Persona&);

istream& operator >>(istream&, class Alumno&);
ostream& operator <<(ostream&, class Alumno&);

istream& operator >>(istream&, class Profesor&);
ostream& operator <<(ostream&, class Profesor&);

#endif /* SOBRECARGA_H */
