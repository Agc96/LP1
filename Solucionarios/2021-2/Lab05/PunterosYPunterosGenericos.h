/*
 * File:   PunterosYPunterosGenericos.h
 * Author: Anthony Gutiérrez
 *
 * Created on 15 de octubre de 2021, 12:35 AM
 */

#ifndef PUNTEROSYPUNTEROSGENERICOS_H
#define PUNTEROSYPUNTEROSGENERICOS_H

#include <iostream>
#include <fstream>
using namespace std;

void cargaDeLibros(void *&);
char *crearCadenaExacta(const char *);
int *crearIntExacto(int);
double *crearDoubleExacto(double);
void *crearArrDinamicoExacto(void **, int);
void reporteDeLibros(void *);

void cargaDeUsuarios(int *&, char *&, char **&);
void incrementarUsuarios(int *&, char *&, char **&, int);
void reporteDeUsuarios(int *, char *, char **);

/* Pregunta 3 */
void reporteUsuariosInhabilitados(void *, int *, char *, char **);
void cargaDeDeudas(void *&, int);
int obtenerMaxDiasPorTipo(char);
char *crearCharExacto(char);
void reporteDeDeudas(void *);
void imprimirDeudasUsuarios(ofstream &, void *, int, char, char *, int &,
        void *, int);
void imprimirCabeceraUsuario(ofstream &arch, int, char, char *, int);
int buscarLibro(void *, char *);
void imprimirLibroEndeudado(ofstream &, void *, int, char, char *, int &, int,
        double, bool &, double &);
double obtenerMoraPorTipo(char);
void imprimirLinea(ofstream &, char);

#endif /* PUNTEROSYPUNTEROSGENERICOS_H */

