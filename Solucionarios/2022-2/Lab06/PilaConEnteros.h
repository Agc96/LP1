/*
 * Archivo: PilaConEnteros.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:09 PM
 */

#ifndef PILACONENTEROS_H
#define PILACONENTEROS_H

#include <iostream>
#include <fstream>
using namespace std;

void *leenumero(ifstream &);
int cmpnumero(const void *, const void *);
void imprimenumero(void *, ofstream &);

#endif /* PILACONENTEROS_H */
