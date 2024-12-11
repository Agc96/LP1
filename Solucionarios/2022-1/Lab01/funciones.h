/*
 * File:   funciones.h
 * Author: Anthony Gutiérrez
 *
 * Created on 18 de abril de 2022, 08:33 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void generarReporte();
void imprimirCabeceraReporte();
void leerDatosInicio(double&, double&, double&, char*);
void procesarClientes(double, double, double, char*, double&, char*, char*,
        double&);
void procesarNombreCliente(char*, double, double, double, char&, double&);
void imprimirCliente(int, char*, int, char, double);
void imprimirDescuento(double, int);
void imprimirCabeceraProductos();
void imprimirProducto(int&, char*, char*, double, double, double, double,
        double&, double&, int, int, int, char*, char*, double&);
void imprimirResumenProductos(int&, double&, double&, char*, double&, char*);
void imprimirResumenReporte(char*, double, char*, char*, double);

// Funciones auxiliares
void imprimirLinea(char);
void reemplazarGuiones(char*);
int longitudCadena(char*);

#endif /* FUNCIONES_H */
