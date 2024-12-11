/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo: funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   18 de agosto de 2023, 12:43 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "funciones.h"
using namespace std;

void elaborarReporte() {
    ifstream archLibros("Libros.csv", ios::in);
    if (not archLibros.is_open()) {
        cout << "ERROR: No se pudo encontrar el archivo Libros.csv" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR: No se pudo crear el archivo Reporte.txt" << endl;
        exit(1);
    }
    archReporte.precision(2);
    archReporte << fixed;
    char codLibro[8], nomLibro[40], autor[40], coma;
    int cantLibros;
    double precio;
    // Impresión de la cabecera
    archReporte << left << setw(10) << "Codigo" << setw(40) << "Nombre" << setw(40) << "Autor"
            << setw(5) << "Cant." << right << setw(10) << "Precio" << endl;
    imprimirLinea(archReporte, '=');
    // Lectura del archivo de entrada
    while (true) {
        archLibros.getline(codLibro, 8, ',');
        if (archLibros.eof()) break;
        archLibros.getline(nomLibro, 40, ',');
        archLibros.getline(autor, 40, ',');
        archLibros >> cantLibros >> coma >> precio >> ws;
        // Impresión en el archivo de salida
        archReporte << left << setw(10) << codLibro << setw(40) << nomLibro << setw(40) << autor
                << right << setfill('0') << setw(5) << cantLibros << setfill(' ') << setw(10) << precio << endl;
    }
}

void imprimirLinea(ofstream &arch, char car) {
    for (int i = 0; i < 105; i++)
        arch.put(car);
    arch << endl;
}
