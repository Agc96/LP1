/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.h
 * Autor:   Anthony Gutiérrez
 * Fecha:   6 de septiembre de 2023, 08:27 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
using namespace std;

void leerClientes(struct Cliente *);
void leerProductos(struct Producto *);
void leerPedidos(struct Cliente *, struct Producto *);
void imprimirReporte(struct Cliente *, struct Producto *);
void imprimirLinea(ofstream &, char);

#endif /* FUNCIONES_H */
