/* 
 * Archivo: Sobrecarga.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 15 de noviembre de 2019, 12:56 PM
 */

#ifndef SOBRECARGA_H
#define SOBRECARGA_H

#include "NumeroMuyGrande.h"

ifstream& operator >> (ifstream&, NumeroMuyGrande&);
ofstream& operator << (ofstream&, NumeroMuyGrande&);

#endif /* SOBRECARGA_H */
