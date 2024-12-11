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

void leerProducto(ifstream& arch, Estructura_ProductosEnAlmacen&,
        Estructura_PedidoRealizado&);

#endif /* FUNCIONES_H */
