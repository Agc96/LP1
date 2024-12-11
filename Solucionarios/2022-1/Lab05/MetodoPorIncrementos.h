/*
 * Archivo: MetodoPorIncrementos.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   13 de mayo de 2022, 08:08 AM
 */

#ifndef METODOPORINCREMENTOS_H
#define METODOPORINCREMENTOS_H

#include <iostream>
#include <fstream>
using namespace std;

void CargaDePedidosYProductos(int **, char ***&, double **&, char ***&, int ***&, const char *);
void InicializarArrPedidos(int **, char ***&, int ***&, int *&, int *&);
void LeerPedido(ifstream &, char *, char *, int &, double &, double &, int &, int &);
int BuscarProducto(char ***, char *);
void AgregarProducto(char ***&, double **&, int &, int &, char *, char *, double, double);
void IncrementarProductos(char ***&, double **&, int, int &);
int BuscarCliente(int **, int);
void AgregarPedido(char ***, int ***, int *, int *, int, char *, int, int);
void IncrementarPedidos(char ***, int ***, int *, int *, int);

void ReporteDePedidosYProductos(int **, char ***, double **, char ***, int ***, const char *);

void ReporteRelacionDePedidos(int **, char ***, char ***, double **, char ***, int ***, const char *);
void ImprimirCabeceraClientes(ofstream &, int **, char ***, int);
void ImprimirPedido(ofstream &, char ***, double **, int ***, int, int, int, double &, double &);

// Funciones auxiliares
void AbrirArchivoLectura(ifstream &, const char *);
void AbrirArchivoEscritura(ofstream &, const char *);
char *CrearCadenaExacta(char *);
void ImprimirLinea(ofstream &, char, int);
void ImprimirFecha(ofstream &, int);

#endif /* METODOPORINCREMENTOS_H */
