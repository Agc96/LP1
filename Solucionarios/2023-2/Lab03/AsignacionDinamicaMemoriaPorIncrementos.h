/*
 * Archivo: AsignacionDinamicaMemoriaPorIncrementos.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   22 de septiembre de 2023, 12:48 PM
 */

#ifndef ASIGNACIONDINAMICAMEMORIAPORINCREMENTOS_H
#define ASIGNACIONDINAMICAMEMORIAPORINCREMENTOS_H

#include <iostream>
#include <fstream>
using namespace std;

void lecturaDeProductos(const char *, char ***&, int *&, double *&);
void incrementarEspaciosProductos(char ***&, int *&, double *&, int &, int &);
void pruebaDeLecturaDeProductos(const char *, char ***, int *, double *);

void lecturaDePedidos(const char *, int *&, char ***&, int ***&);
int buscarFecha(int *, int, int);
void incrementarEspaciosFechas(int *&, char ***&, int ***&, int *&, int *&,
        int &, int &);
int agregarFechaOrdenada(int *, char ***, int ***, int *, int *, int, int);
void agregarPedido(char *, int, int, char **&, int **&, int &, int &);
void pruebaDeLecturaDePedidos(const char *, int *, char ***, int ***);

void reporteDeEntregaDePedidos(const char *, char ***, int *, double *, int *,
        char ***, int ***);
void imprimirListaPedidos(ofstream &, char ***, int *, double *, char **,
        int **, double &, double &);
int buscarProducto(char ***, char *);

/* Funciones auxiliares */
void abrirArchivoEntrada(ifstream &, const char *);
void crearArchivoSalida(ofstream &, const char *);
char *leerCadena(ifstream &, char = ',');
void imprimirFecha(ofstream &, int);
void imprimirLinea(ofstream &, char, int);

#endif /* ASIGNACIONDINAMICAMEMORIAPORINCREMENTOS_H */
