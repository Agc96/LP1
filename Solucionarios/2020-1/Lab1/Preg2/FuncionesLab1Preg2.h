/* 
 * Archivo: FuncionesLab1Preg2.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef FUNCIONESLAB1PREG2_H
#define FUNCIONESLAB1PREG2_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

void *leerCliente(ifstream &);
void imprimirCliente(ofstream &, void *);
void atiendeCola(void *&);

int *crearEntero(int);
char *crearCadena(char *);
double *crearDecimal(double);

#endif /* FUNCIONESLAB1PREG2_H */
