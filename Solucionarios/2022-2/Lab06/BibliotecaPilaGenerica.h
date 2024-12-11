/*
 * Archivo: BibliotecaPilaGenerica.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   30 de octubre de 2022, 12:08 PM
 */

#ifndef BIBLIOTECAPILAGENERICA_H
#define BIBLIOTECAPILAGENERICA_H

#include <iostream>
#include <fstream>
using namespace std;

void cargaarreglo(void *&, int (*)(const void *, const void *),
        void *(*)(ifstream &), const char *);
void cargapila(void *&, void *);
void muevepila(void *, void *&);
void hanoi(int, void *, void *, void *);
void imprimepila(void *, void (*)(void *, ofstream &), const char *);

void *creapila();
void push(void *, void *);
void* pop(void *);
bool pilavacia(void *);
int cantelempila(void *);

#endif /* BIBLIOTECAPILAGENERICA_H */
