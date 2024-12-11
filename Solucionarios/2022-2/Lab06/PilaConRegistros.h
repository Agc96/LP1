/*
 * Archivo: PilaConRegistros.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:09 PM
 */

#ifndef PILACONREGISTROS_H
#define PILACONREGISTROS_H

#include <iostream>
#include <fstream>
using namespace std;

void *leeregistro(ifstream &);
int cmpregistro(const void *, const void *);
void imprimeregistro(void *, ofstream &);
void imprimeLinea(ofstream &, int, char);

#endif /* PILACONREGISTROS_H */
