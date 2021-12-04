/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Funciones.h
 * Author: Anthony
 *
 * Created on 12 de noviembre de 2021, 09:28 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include "Usuario.h"
#include "Libro.h"
using namespace std;

void leerUsuarios(Usuario *);

void leerLibros(Libro *);

void procesarPrestamos(Usuario *, Libro *);
int buscarUsuario(Usuario*, LibroPrestado&);
int buscarLibro(Libro*, LibroPrestado&);

void actualizarUsuarios(Usuario *);

void reporteUsuarios(Usuario *);

void reporteLibros(Libro *);

// Funciones auxiliares
ifstream abrirArchivo(const char *);
ofstream crearArchivo(const char *);

#endif /* FUNCIONES_H */
