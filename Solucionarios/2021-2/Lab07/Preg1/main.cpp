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

int main() {
    ifstream archUsuarios = abrirArchivo("Usuarios.csv");
    ifstream archPrestamos = abrirArchivo("RegistroDePrestamos.csv");
    ifstream archLibros = abrirArchivo("Libros.csv");
    ofstream archReporte = crearArchivo("Reporte.txt");
    Usuario usuario;
    LibroPrestado prestamo;
    Libro libro;
    // Lectura de datos
    archUsuarios >> usuario;
    archPrestamos >> prestamo;
    archLibros >> libro;
    // Operadores sobrecargados
    usuario += prestamo;
    libro += prestamo;
    usuario * 20210930;
    // Impresión de datos
    archReporte << usuario << endl;
    archReporte << prestamo << endl;
    archReporte << libro;
    return 0;
}
