/* 
 * Archivo: BibliotecaColaGenerica.h
 * Autor:   Anthony Gutiérrez
 */

#ifndef BIBLIOTECACOLAGENERICA_H
#define BIBLIOTECACOLAGENERICA_H

#include <iostream>
#include <fstream>
using namespace std;

void creaCola(void *&, void *(*)(ifstream &));
void encola(void *, void *);
void *desencola(void *);
bool colaVacia(void *);
void imprimir(void *, void (*)(ofstream &, void *));

#endif /* BIBLIOTECACOLAGENERICA_H */
