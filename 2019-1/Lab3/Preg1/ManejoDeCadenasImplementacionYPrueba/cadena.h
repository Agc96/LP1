/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: cadena.h
 * Autor:   Anthony Gutiérrez
 * Código:  20130095
 * Creado el 26 de septiembre de 2019, 05:42 PM
 */

#ifndef CADENA_H
#define CADENA_H

#include <iostream>
using namespace std;

struct Cadena {
    char* cadena;
    int longitud;
    int capacidad;
};

void inicializa(Cadena&, int = 0);
void leer(Cadena&, char = '\n');
void imprimir(Cadena&);
int longitud(Cadena&);
int capacidad(Cadena&);
void recortar(Cadena&);
void intercambiar(Cadena&, Cadena&);

// Cadena operator += (Cadena&);
Cadena operator + (Cadena&, Cadena&);
bool operator == (Cadena&, Cadena&);
bool operator > (Cadena&, Cadena&);
bool operator < (Cadena&, Cadena&);
istream& operator >> (istream&, Cadena&);
ostream& operator << (ostream&, Cadena&);

#endif /* CADENA_H */
