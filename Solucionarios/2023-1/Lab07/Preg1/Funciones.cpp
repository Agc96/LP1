/*
 * Archivo: Funciones.cpp
 * Autor:   Anthony Gutiérrez
 * Fecha:   10 de junio de 2023, 10:08 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "AlumnoNota.h"
#include "Nota.h"
#include "Alumno.h"
#include "Funciones.h"
using namespace std;

void pruebaClases(const char *nomArchDatos, const char *nomArchReporte) {
    ifstream archDatos;
    ofstream archReporte;
    abrirArchivoEntrada(archDatos, nomArchDatos);
    abrirArchivoSalida(archReporte, nomArchReporte);
    archReporte << fixed << setprecision(2);
    AlumnoNota alumnoNota;
    Nota nota;
    Alumno alumno;
    archDatos >> alumno >> alumnoNota;
    (alumnoNota & nota);
    alumno += nota;
    archReporte << alumno;
}

/* Funciones auxiliares */

void abrirArchivoEntrada(ifstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::in);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}

void abrirArchivoSalida(ofstream &arch, const char *nomArch) {
    arch.open(nomArch, ios::out);
    if (!arch) {
        cerr << "No se pudo abrir el archivo " << nomArch << endl;
        exit(1);
    }
}
