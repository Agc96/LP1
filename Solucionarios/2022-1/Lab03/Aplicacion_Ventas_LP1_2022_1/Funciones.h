/*
 * Archivo: Funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   2 de mayo de 2022, 08:51 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include "Estructuras.h"
using namespace std;

void procesarClientes(Estructura_ClienteRegistrado[]);

void procesarProductos(Estructura_ClienteRegistrado[],
        Estructura_ProductosEnAlmacen[]);
void leerDatosProducto(ifstream&, Estructura_ProductosEnAlmacen&,
        Estructura_PedidoRealizado&, int&);
int buscarCliente(Estructura_ClienteRegistrado[], int);

void generarReporte(Estructura_ClienteRegistrado[],
        Estructura_ProductosEnAlmacen[]);

#endif /* FUNCIONES_H */
