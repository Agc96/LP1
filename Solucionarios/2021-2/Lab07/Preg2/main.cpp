/*
 * File:   main.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 12 de noviembre de 2021, 09:15 AM
 */

#include <iostream>
#include <fstream>
#include "Funciones.h"
#include "Usuario.h"
#include "LibroPrestado.h"
#include "Libro.h"
using namespace std;

#define MAX_USUARIOS 50
#define MAX_LIBROS 50

int main() {
    Usuario usuarios[MAX_USUARIOS];
    Libro libros[MAX_LIBROS];
    leerUsuarios(usuarios);
    leerLibros(libros);
    procesarPrestamos(usuarios, libros);
    actualizarUsuarios(usuarios);
    reporteUsuarios(usuarios);
    reporteLibros(libros);
    return 0;
}
