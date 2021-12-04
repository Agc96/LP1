/*
 * File:   main.cpp
 * Author: Anthony Gutiérrez
 *
 * Created on 15 de octubre de 2021, 12:34 AM
 */

#include "PunterosYPunterosGenericos.h"

int main() {
    void *libros;
    char *tipo, **nombre;
    int *carne;
    cargaDeLibros(libros);
    reporteDeLibros(libros);
    cargaDeUsuarios(carne, tipo, nombre);
    reporteDeUsuarios(carne, tipo, nombre);
    reporteUsuariosInhabilitados(libros, carne, tipo, nombre);
    return 0;
}
