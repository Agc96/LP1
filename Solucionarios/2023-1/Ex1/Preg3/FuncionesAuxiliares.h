/*
 * Archivo: FuncionesAuxiliares.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   20 de mayo de 2023, 10:09 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
using namespace std;

char *leerCadenaDinamicaYExacta(ifstream &, char);
void imprimirLinea(ofstream &, char, int);

// Función de prueba brindada durante el examen en una biblioteca estática
void ImprimeAlumno(void *);

#endif /* FUNCIONESAUXILIARES_H */
