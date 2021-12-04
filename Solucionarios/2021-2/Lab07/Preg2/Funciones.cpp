/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "Funciones.h"
using namespace std;

void leerUsuarios(Usuario* usuarios) {
    ifstream arch = abrirArchivo("Usuarios.csv");
    int cant = 0;
    while (1) {
        arch >> usuarios[cant];
        if (arch.eof()) break;
        cant++;
    }
}

void leerLibros(Libro* libros) {
    ifstream arch = abrirArchivo("Libros.csv");
    int cant = 0;
    while (1) {
        arch >> libros[cant];
        if (arch.eof()) break;
        cant++;
    }
}

void procesarPrestamos(Usuario *usuarios, Libro* libros) {
    ifstream arch = abrirArchivo("RegistroDePrestamos.csv");
    LibroPrestado prestamo;
    int posLibro, posUsuario;
    while (1) {
        arch >> prestamo;
        if (arch.eof()) break;
        // Buscar el usuario para añadir el préstamo
        posUsuario = buscarUsuario(usuarios, prestamo);
        if (posUsuario != -1) {
            usuarios[posUsuario] += prestamo;
        }
        // Buscar el libro para añadir el préstamo
        posLibro = buscarLibro(libros, prestamo);
        if (posLibro != -1) {
            libros[posLibro] += prestamo;
        }
    }
}

int buscarUsuario(Usuario *usuarios, LibroPrestado& prestamo) {
    for (int i = 0; usuarios[i].GetCarne(); i++) {
        if (usuarios[i].GetCarne() == prestamo.getCarne()) return i;
    }
    return -1;
}

int buscarLibro(Libro* libros, LibroPrestado& prestamo) {
    char codLibroLeido[10], codLibroPrestamo[10];
    prestamo.getCodigoLib(codLibroPrestamo);
    for (int i = 0; libros[i].GetStock(); i++) {
        libros[i].GetCodigo(codLibroLeido);
        if (strcmp(codLibroLeido, codLibroPrestamo) == 0) return i;
    }
    return -1;
}

void actualizarUsuarios(Usuario* usuarios) {
    int fecha;
    // Leer la fecha solicitada
    cout << "Ingrese una fecha en el formato AAAAMMDD: ";
    cin >> fecha;
    // Actualizar los usuarios 
    for (int i = 0; usuarios[i].GetCarne(); i++) {
        usuarios[i] * fecha;
    }
}

void reporteUsuarios(Usuario* usuarios) {
    ofstream arch = crearArchivo("ReporteUsuarios.txt");
    for (int i = 0; usuarios[i].GetCarne(); i++) {
        arch << usuarios[i] << endl;
    }
}

void reporteLibros(Libro* libros) {
    ofstream arch = crearArchivo("ReporteLibros.txt");
    for (int i = 0; libros[i].GetStock(); i++) {
        arch << libros[i] << endl;
    }
}

/* Funciones auxiliares */

ifstream abrirArchivo(const char *nomArch) {
    ifstream arch(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}

ofstream crearArchivo(const char *nomArch) {
    ofstream arch(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo crear el archivo " << nomArch << endl;
        exit(1);
    }
    return arch;
}
